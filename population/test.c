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
    int increase;
    int decrease;
    int newPop;
    printf("Year %d: %d deer\n", years, startPop);
    while (startPop < endPop)
    {
        increase = startPop / 3;
        decrease = startPop / 4;
        newPop = startPop + increase - decrease;
        years++;
        printf("Year %d: %d + %d - %d = %d deer\n", years, startPop, increase, decrease, newPop);
        startPop = newPop;
    }

    // TODO: Print number of years
    printf("%d\n", years);
}
