import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter for USD formatting
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (not signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Connect to SQLite database
db = SQL("sqlite:///finance.db")


# ----------------------------
# INDEX (homepage)
# ----------------------------
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Get user's stocks and sum shares per symbol
    holdings = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",
        user_id,
    )

    total = 0
    for stock in holdings:
        quote = lookup(stock["symbol"])
        stock["price"] = quote["price"]
        stock["name"] = quote["name"]
        stock["total"] = stock["price"] * stock["shares"]
        total += stock["total"]

    # Get user's cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    grand_total = cash + total

    return render_template("index.html", holdings=holdings, cash=cash, total=grand_total)


# ----------------------------
# REGISTER
# ----------------------------
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    # Validate input
    if not username:
        return apology("must provide username", 400)
    elif not password:
        return apology("must provide password", 400)
    elif password != confirmation:
        return apology("passwords do not match", 400)

    # Hash password
    hash_pw = generate_password_hash(password)

    try:
        new_user_id = db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_pw
        )
    except ValueError:
        return apology("username already exists", 400)

    # Remember user
    session["user_id"] = new_user_id
    return redirect("/")


# ----------------------------
# LOGIN
# ----------------------------
@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any previous user_id
    session.clear()

    if request.method == "GET":
        return render_template("login.html")

    username = request.form.get("username")
    password = request.form.get("password")

    if not username:
        return apology("must provide username", 403)
    elif not password:
        return apology("must provide password", 403)

    # Query database for username
    rows = db.execute("SELECT * FROM users WHERE username = ?", username)
    if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
        return apology("invalid username and/or password", 403)

    # Remember user
    session["user_id"] = rows[0]["id"]

    return redirect("/")


# ----------------------------
# LOGOUT
# ----------------------------
@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")


# ----------------------------
# QUOTE
# ----------------------------
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    symbol = request.form.get("symbol")
    if not symbol:
        return apology("must provide symbol")

    quote = lookup(symbol)
    if not quote:
        return apology("invalid symbol")

    return render_template("quoted.html", quote=quote)


# ----------------------------
# BUY
# ----------------------------
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if not symbol:
        return apology("must provide symbol")
    if not shares or not shares.isdigit() or int(shares) <= 0:
        return apology("shares must be a positive integer")

    quote = lookup(symbol)
    if not quote:
        return apology("invalid symbol")

    shares = int(shares)
    price = quote["price"]
    cost = price * shares

    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    if cash < cost:
        return apology("not enough cash")

    db.execute(
        "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
        user_id,
        symbol.upper(),
        shares,
        price,
    )
    db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cost, user_id)

    return redirect("/")


# ----------------------------
# SELL
# ----------------------------
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "GET":
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",
            user_id,
        )
        return render_template("sell.html", symbols=[s["symbol"] for s in symbols])

    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if not symbol:
        return apology("must select symbol")
    if not shares or not shares.isdigit() or int(shares) <= 0:
        return apology("shares must be positive integer")

    shares = int(shares)
    owned = db.execute(
        "SELECT SUM(shares) as total FROM transactions WHERE user_id = ? AND symbol = ?",
        user_id,
        symbol,
    )[0]["total"]

    if owned is None or owned < shares:
        return apology("not enough shares")

    quote = lookup(symbol)
    price = quote["price"]

    db.execute(
        "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
        user_id,
        symbol,
        -shares,
        price,
    )
    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", shares * price, user_id)

    return redirect("/")


# ----------------------------
# HISTORY
# ----------------------------
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT symbol, shares, price, transacted_at FROM transactions WHERE user_id = ? ORDER BY transacted_at DESC",
        user_id,
    )
    return render_template("history.html", transactions=transactions)
