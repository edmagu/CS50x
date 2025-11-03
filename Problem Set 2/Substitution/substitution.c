// substitution/substitution.c
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
bool valid_key(string key);
void encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    // Check number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    // Validate key
    if (!valid_key(key))
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    // Get plaintext
    string plaintext = get_string("plaintext:  ");

    // Print ciphertext
    printf("ciphertext: ");
    encrypt(plaintext, key);
    printf("\n");

    return 0;
}

// Validate that key is 26 unique letters
bool valid_key(string key)
{
    int length = strlen(key);
    if (length != 26)
    {
        return false;
    }

    bool seen[26] = {false};

    for (int i = 0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int index = toupper(key[i]) - 'A';
        if (seen[index])
        {
            // duplicate letter found
            return false;
        }
        seen[index] = true;
    }
    return true;
}

// Encrypt and print ciphertext
void encrypt(string plaintext, string key)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char c = plaintext[i];

        if (isupper(c))
        {
            int index = c - 'A';
            char cipher_char = toupper(key[index]);
            printf("%c", cipher_char);
        }
        else if (islower(c))
        {
            int index = c - 'a';
            char cipher_char = tolower(key[index]);
            printf("%c", cipher_char);
        }
        else
        {
            printf("%c", c);
        }
    }
}
