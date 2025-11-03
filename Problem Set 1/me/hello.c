#include <cs50.h>
#include <stdio.h>
// Define function and make it return no value
int main(void)
{
    // Get the name
    string name = get_string("What's your name? ");
    // Print the name with hello "%s!\n" is a string placeholder
    printf("hello, %s\n", name);
    return 0;
}
