#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int checkAlpha[26] = {};
int isValid(string cipher);
string transmute(string cipher, string text);
int isLetter(char character);
char transmuteLetter(char letter, string cipher);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int code = isValid(argv[1]);
    if (code == 0)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    else if (code == 2)
    {
        printf("Key must contain only letters\n");
        return 1;
    }
    else if (code == 3)
    {
        printf("Key must not repeat letters\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    string cipher = transmute(argv[1], text);

    printf("ciphertext: %s\n", cipher);
    return 0;
}

int isValid(string cipher)
{
    int length = strlen(cipher);

    if (length != 26)
    {
        return 0;
    }

    char letter;
    for (int i = 0; i < length; i++)
    {
        letter = cipher[i];
        if (letter >= 'a' && letter <= 'z')
        {
            letter -= 32;
        }
        else if (letter < 'A' || letter > 'Z')
        {
            return 2;
        }

        if (checkAlpha[letter - 65])
        {
            return 3;
        }
        checkAlpha[letter - 65] = 1;
    }

    return 1;
}

string transmute(string cipher, string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isLetter(text[i]))
        {
            text[i] = transmuteLetter(text[i], cipher);
        }
    }

    return text;
}

char transmuteLetter(char letter, string cipher)
{
    int isUpper = letter <= 'Z';
    int index;
    if (isUpper)
    {
        letter = cipher[letter - 'A'];
    }
    else
    {
        letter = cipher[letter - 'a'];
    }

    if (isUpper && letter >= 'a' && letter <= 'z')
    {
        letter -= 32;
    }
    else if (!isUpper && letter >= 'A' && letter <= 'Z')
    {
        letter += 32;
    }

    return letter;
}

int isLetter(char letter)
{
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}