#include <cs50.h>
#include <math.h>
#include <stdio.h>

int luhn(long number);
long pow10(int power);
int getDigit(long num, int place);
int getDigits(long num, int place, int toPlace);
int checkAMEX(long num);
int checkMASTERCARD(long num);
int checkVISA(long num);

int main(void)
{
    long credit = get_long("Number: ");

    // checks if valid number
    if (credit / pow10(16) > 0 || credit / pow10(12) == 0 || luhn(credit) == 1)
    {
        printf("INVALID\n");
        return 0;
    }

    if (checkAMEX(credit) == 0)
    {
        printf("AMEX\n");
    }
    else if (checkMASTERCARD(credit) == 0)
    {
        printf("MASTERCARD\n");
    }
    else if (checkVISA(credit) == 0)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int luhn(long credit)
{
    long total = 0;
    int digit;
    // get every other digit, times it by 2, add it to total
    for (int i = 1; i < 16; i += 2)
    {
        digit = getDigit(credit, i) * 2;
        if (digit / 10 == 1)
        {
            total++;
            total += digit % 10;
        }
        else
        {
            total += digit;
        }
    }

    for (int i = 0; i < 16; i += 2)
    {
        total += getDigit(credit, i);
    }

    if (total % 10 == 0)
    {
        return 0;
    }
    return 1;
}

long pow10(int power)
{
    return (long) pow(10, power);
}

// reverse 0 indexed
int getDigit(long num, int place)
{
    return num % pow10(place + 1) / pow10(place);
}

// also reverse 0 indexed
int getDigits(long num, int place, int toPlace)
{
    return num % pow10(place + 1) / pow10(toPlace);
}

int checkAMEX(long num)
{
    int digits = getDigits(num, 14, 13);
    if (digits == 34 || digits == 37)
    {
        return 0;
    }
    return 1;
}

int checkMASTERCARD(long num)
{
    int digits = getDigits(num, 15, 14);
    if (digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55)
    {
        return 0;
    }
    return 1;
}

int checkVISA(long num)
{
    int digit1 = getDigit(num, 15);
    int digit2 = getDigit(num, 12);
    if (digit1 == 4 || (num / pow10(13) == 0 && digit2 == 4))
    {
        return 0;
    }
    return 1;
}