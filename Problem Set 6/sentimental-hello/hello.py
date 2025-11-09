




def hello():
    try:
        user_input: str = input("Enter your name: ")
        print(f"Hello, {user_input}")
    except ValueError:
        print("Please enter a valid number.")

if __name__ == "__main__":
    hello()