def luhn_checksum(n: int) -> int:
    total = 0
    double_next = False
    while n > 0:
        d = n % 10
        if double_next:
            x = d * 2
            total += x // 10 + x % 10
        else:
            total += d
        double_next = not double_next
        n //= 10
    return total % 10

def length_of(n: int) -> int:
    length = 0
    while n > 0:
        length += 1
        n //= 10
    return length

def main():
    while True:
        try:
            number = int(input("Number: "))
            break
        except ValueError:
            continue

    if number <= 0:
        print("INVALID")
        return

    n = number
    length = length_of(n)

    tmp = n
    while tmp >= 100:
        tmp //= 10
    first_two = int(tmp)
    first_one = first_two // 10

    if luhn_checksum(number) != 0:
        print("INVALID")
        return

    if length == 15 and (first_two == 34 or first_two == 37):
        print("AMEX")
    elif length == 16 and (51 <= first_two <= 55):
        print("MASTERCARD")
    elif (length == 13 or length == 16) and first_one == 4:
        print("VISA")
    else:
        print("INVALID")

if __name__ == "__main__":
    main()
