#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char shiftLetter(char letter, int shift);
char shiftUpper(char letter, int shift);
char shiftLower(char letter, int shift);
int strToInt(string text);
long pow10(int power);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage ./casear key\n");
        return 1;
    }

    int num = strToInt(argv[1]);
    if (num == -1)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    int shift = num % 26;
    if (shift <= 0)
    {
        printf("Usage ./casear key\n");
        return 1;
    }
    string text = get_string("plaintext: ");

    printf("ciphertext: ");
    char newChar;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        newChar = shiftLetter(text[i], shift);
        // debug
        // printf("%c %i\n", newChar, newChar);
        printf("%c", newChar);
    }
    printf("\n");
}

char shiftLetter(char letter, int shift)
{
    if (letter >= 'A' && letter <= 'Z')
    {
        return shiftUpper(letter, shift);
    }
    else if (letter >= 'a' && letter <= 'z')
    {
        return shiftLower(letter, shift);
    }
    else
    {
        return letter;
    }
}

char shiftUpper(char letter, int shift)
{
    letter += shift;
    if (letter > 'Z')
    {
        letter -= 26;
    }
    return letter;
}

char shiftLower(char letter, int shift)
{
    letter -= 26;
    letter += shift;
    if (letter < 'a')
    {
        letter += 26;
    }
    return letter;
}

int strToInt(string text)
{
    int num = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= '0' && text[i] <= '9')
        {
            num += (text[i] - '0') * pow10(n - i - 1);
        }
        else
        {
            return -1;
        }
    }
    return num;
}

long pow10(int power)
{
    return (long) pow(10, power);
}