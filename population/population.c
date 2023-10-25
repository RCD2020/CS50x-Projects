#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startPop = 0;
    while (startPop < 9)
    {
        startPop = get_int("How many deer? ");
    }
    // TODO: Prompt for end size
    int endPop = 0;
    while (endPop < startPop)
    {
        endPop = get_int("What should the final population be? ");
    }

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (startPop < endPop)
    {
        startPop += (startPop / 3) - (startPop / 4);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}
