#include <cs50.h>
#include <stdio.h>

// declare functions
void left(int size, int spaces);
void right(int size);
void line(int size, int spaces);

int main(void)
{
    // get user input size between 1 to 8 inclusive
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (size < 1 || size > 8);

    // loops through range 1 to size inclusive
    for (int i = 1; i <= size; i++)
    {
        line(i, size - i);
    }
}

void left(int size, int spaces)
{
    // print spaces, 1 to spaces inclusive
    for (int i = 1; i <= spaces; i++)
    {
        printf(" ");
    }

    // print #, 1 to size inclusive
    for (int i = 1; i <= size; i++)
    {
        printf("#");
    }
}

void right(int size)
{
    // print #, 1 to # inclusive
    for (int i = 1; i <= size; i++)
    {
        printf("#");
    }
}

void line(int size, int spaces)
{
    // print line and start new line
    left(size, spaces);
    printf("  ");
    right(size);
    printf("\n");
}