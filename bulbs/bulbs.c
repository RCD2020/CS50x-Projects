#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;
const int N = 8;
const int POWERS[N] = {128, 64, 32, 16, 8, 4, 2, 1};

void print_bulb(int bit);
void letter2print(char letter);

int main(void)
{
    // TODO
    string text = get_string("Message: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        letter2print(text[i]);
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

void letter2print(char letter)
{
    int num = (int) letter;

    for (int i = 0; i < N; i++)
    {
        if (num >= POWERS[i])
        {
            printf("\U0001F7E1");
            num -= POWERS[i];
        }
        else
        {
            printf("\U000026AB");
        }
    }
    printf("\n");
}
