import os
from flask import Flask, render_template, request, redirect, url_for, session
from music_utils import organize_music

app = Flask(__name__)
app.secret_key = "super_secure_autodj_key"

# Ensure uploads directory exists
UPLOAD_FOLDER = "uploads"
os.makedirs(UPLOAD_FOLDER, exist_ok=True)
app.config["UPLOAD_FOLDER"] = UPLOAD_FOLDER


@app.route("/")
def index():
    return render_template("index.html")



@app.route("/upload", methods=["POST"])
def upload():
    # Try to get files under both common field names
    files = request.files.getlist("files[]") or request.files.getlist("files")

    # If user clicked submit with no files, just go back to the homepage
    if not files or (len(files) == 1 and files[0].filename == ""):
        # either redirect:
        return redirect(url_for("index"))
        # or, if you prefer to stay on page:
        # return ("", 204)

    results = []
    for f in files:
        if f and f.filename:
            result = organize_music(f, app.config["UPLOAD_FOLDER"])
            results.append(result)

    # if nothing valid was processed, also just go back
    if not results:
        return redirect(url_for("index"))

    session["results"] = results
    return ("", 200)


@app.route("/results")
def results():
    results = session.get("results", [])
    return render_template("results.html", results=results)


if __name__ == "__main__":
    app.run(debug=True)
