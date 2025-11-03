#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt the user for height between 1 and 8 inclusive
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // For each row
    for (int row = 1; row <= height; row++)
    {
        // Print leading spaces for the left pyramid
        for (int spaces = height - row; spaces > 0; spaces--)
        {
            printf(" ");
        }

        // Print left pyramid hashes
        for (int left_hash = 1; left_hash <= row; left_hash++)
        {
            printf("#");
        }

        // Print the 2-space gap
        printf("  ");

        // Print right pyramid hashes
        for (int right_hash = 1; right_hash <= row; right_hash++)
        {
            printf("#");
        }

        // Move to the next line
        printf("\n");
    }
}
