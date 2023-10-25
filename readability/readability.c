#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isPunct(char character);
int isLetter(char character);
void debugDouble(double data, string tag);
void debugInt(int data, string tag);

int main(void)
{
    int sentences = 0;
    int words = 1;
    int letters = 0;
    string text = get_string("Text: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
        else if (isPunct(text[i]))
        {
            sentences++;
        }
        else if (isLetter(text[i]))
        {
            letters++;
        }
    }

    double lettersPer100Words = (double) letters / words * 100;
    double sentencesPer100Words = (double) sentences / words * 100;
    int index = 0.0588 * lettersPer100Words - 0.296 * sentencesPer100Words - 15.8 + 0.5;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

    // debugInt(letters, "letters");
    // debugInt(words, "words");
    // debugInt(sentences, "sentences");

    // debugDouble(lettersPer100Words, "L");
    // debugDouble(sentencesPer100Words, "S");

    // debugInt(index, "index");
}

int isPunct(char character)
{
    return character == '.' || character == '!' || character == '?';
}

int isLetter(char character)
{
    return (character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z');
}

void debugDouble(double data, string tag)
{
    printf("%s: %f\n", tag, data);
}

void debugInt(int data, string tag)
{
    printf("%s: %i\n", tag, data);
}