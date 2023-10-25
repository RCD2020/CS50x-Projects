#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Gets user input for size of blocks, between 1 and 8 inclusive
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (size < 1 || size > 8);

    // Loops through range 1 to size inclusive.
    for (int i = 1; i <= size; i++)
    {
        // Writes spaces, amount = size - iteration
        for (int j = 1; j <= size - i; j++)
        {
            printf(" ");
        }

        // Writes #s, amount = iteration
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}