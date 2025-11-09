def mario_pyramid():
    """Prints a Mario-style pyramid based on user input height."""
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                break
        except ValueError:
            continue

    for i in range(1, height + 1):
        # Print leading spaces, left hashes, two spaces, and right hashes
        print(" " * (height - i) + "#" * i + "  " + "#" * i)

if __name__ == "__main__":
    mario_pyramid()