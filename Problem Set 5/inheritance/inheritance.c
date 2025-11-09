#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

// Function prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele(void);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a family with three generations
    person *p = create_family(3);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // Allocate memory for new person
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    // Base case: oldest generation
    if (generations <= 1)
    {
        p->parents[0] = NULL;
        p->parents[1] = NULL;
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }
    else
    {
        // Recursive case: create two parents
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Inherit one allele from each parent, chosen randomly
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }

    return p;
}

// Free all allocated memory recursively
void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }

    free_family(p->parents[0]);
    free_family(p->parents[1]);
    free(p);
}

// Print each generation of the family
void print_family(person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }

    // Indentation based on generation level
    for (int i = 0; i < generation * 4; i++)
    {
        printf(" ");
    }

    printf("Generation %i, blood type %c%c\n",
           generation, p->alleles[0], p->alleles[1]);

    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly choose one of three alleles
char random_allele(void)
{
    int r = rand() % 3;
    switch (r)
    {
        case 0: return 'A';
        case 1: return 'B';
        default: return 'O';
    }
}
