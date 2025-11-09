// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
// A good rule: large enough to reduce collisions, small enough for memory
const unsigned int N = 65536; // 2^16 buckets → balance speed & space

// Hash table
node *table[N];

// Word counter
unsigned int word_count = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 hash algorithm by Dan Bernstein (adapted)
    unsigned long hash = 5381;
    int c;
    while ((c = *word++))
    {
        c = tolower(c);
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, false otherwise
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    // Read each word in dictionary
    while (fscanf(file, "%45s", word) != EOF)
    {
        // Create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy word into node
        strcpy(n->word, word);
        n->next = NULL;

        // Hash word to find bucket index
        unsigned int index = hash(word);

        // Insert node at head of linked list
        n->next = table[index];
        table[index] = n;

        word_count++;
    }

    fclose(file);
    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lower[LENGTH + 1];
    int len = strlen(word);

    // Normalize to lowercase
    for (int i = 0; i < len; i++)
    {
        lower[i] = tolower(word[i]);
    }
    lower[len] = '\0';

    // Hash word to find bucket
    unsigned int index = hash(lower);

    // Traverse linked list in that bucket
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lower) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Returns number of words in dictionary if loaded, else 0
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
