// credit/credit.c
#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

static int luhn_checksum(long long n)
{
    int sum = 0;
    bool double_next = false;

    while (n > 0)
    {
        int d = n % 10;
        if (double_next)
        {
            int x = d * 2;
            sum += (x / 10) + (x % 10);
        }
        else
        {
            sum += d;
        }
        double_next = !double_next;
        n /= 10;
    }
    return sum % 10;
}

static int length_of(long long n)
{
    int len = 0;
    while (n > 0)
    {
        len++;
        n /= 10;
    }
    return len;
}

int main(void)
{
    long long number = get_long("Number: ");

    if (number <= 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Keep originals for checks
    long long n = number;

    // Compute length
    int len = length_of(n);

    // Grab first two digits and first digit
    long long tmp = n;
    while (tmp >= 100)
    {
        tmp /= 10;
    }
    int first_two = (int) tmp;
    int first_one = first_two / 10;

    // Luhn validity
    if (luhn_checksum(number) != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Identify issuer
    if (len == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if (len == 16 && (first_two >= 51 && first_two <= 55)) // classic MasterCard range for this problem
    {
        printf("MASTERCARD\n");
    }
    else if ((len == 13 || len == 16) && first_one == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
