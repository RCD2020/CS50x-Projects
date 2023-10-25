// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 500;

// Hash table
node *table[N];

// functions
void copystr(char destination[], char str[], int length);
void showDic(void);
int compstr(char dicstr[], const char str[]);
int isLetter(char letter);

// hash functions
unsigned int byFirstLetter(const char *word); // N = 26
unsigned int byLength(const char *word);      // N = LENGTH + 1
unsigned int byASCIItotal(const char *word);  // N = any real number

// prints out hash data if != 0
int SHOWHASH = 0;

// size of dictionary
unsigned int dicsize;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hashNum = hash(word);
    node *cursor = table[hashNum];
    char code;

    while (cursor != NULL)
    {
        code = compstr(cursor->word, word);
        if (code == 0)
        {
            return true;
        }
        else if (code == 2)
        {
            return false;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    // return byFirstLetter(word); // N = 26
    // return byLength(word);      // N = LENGTH + 1
    return byASCIItotal(word); // N = any real number
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // void out table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("%s not found\n", dictionary);
        return false;
    }

    char cursor = '\0';
    char str[LENGTH + 1];
    int index = 0;
    while (fread(&cursor, sizeof(char), 1, input))
    {
        if (cursor != '\n')
        {
            str[index] = cursor;
            index++;
        }
        else
        {
            str[index] = '\0';
            node *tmpNode = malloc(sizeof(node));
            if (tmpNode == NULL)
            {
                return false;
            }
            copystr(tmpNode->word, str, LENGTH + 1);
            unsigned int hashNum = hash(str);
            tmpNode->next = table[hashNum];
            table[hashNum] = tmpNode;

            index = 0;
            dicsize++;
        }
    }

    fclose(input);

    // test to see it's filled correctly
    if (SHOWHASH)
    {
        showDic();
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dicsize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *freeable;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            freeable = cursor;
            cursor = cursor->next;
            free(freeable);
        }
    }

    return true;
}

void copystr(char destination[], char str[], int length)
{
    for (int i = 0; i < length; i++)
    {
        destination[i] = str[i];
    }
}

void showDic(void)
{
    node *curNode;
    for (int i = 0; i < N; i++)
    {
        printf("[%i] -> ", i);

        curNode = table[i];
        while (curNode != NULL)
        {
            printf("%s -> ", curNode->word);
            curNode = curNode->next;
        }
        printf("NULL\n");
    }
}

int compstr(char dicstr[], const char str[])
{
    // 0: is same word
    // 1: not same word, but continue
    // 2: not same word, and end
    char letter;

    for (int i = 0; i < LENGTH + 1; i++)
    {
        letter = str[i];
        if (letter >= 'A' && letter <= 'Z')
        {
            letter += 32;
        }

        if (dicstr[i] != letter)
        {
            if (dicstr[i] > letter && isLetter(dicstr[i]) && isLetter(letter))
            {
                return 2;
            }
            return 1;
        }
        if (dicstr[i] == '\0')
        {
            return 0;
        }
    }
    return 0;
}

int isLetter(char letter)
{
    if (letter >= 'a' && letter <= 'z')
    {
        return 1;
    }
    return 0;
}

unsigned int byFirstLetter(const char *word)
{
    // N = 26
    return (toupper(word[0]) - 'A') % N;
}

unsigned int byLength(const char *word)
{
    // N = LENGTH + 1
    unsigned int counter = 0;
    for (int i = 1; i < LENGTH + 1; i++)
    {
        if (word[i] == '\0')
        {
            break;
        }
        counter++;
    }

    return counter % N;
}

unsigned int byASCIItotal(const char *word)
{
    // N = any real number
    unsigned int total = 0;
    for (int i = 0; i < LENGTH + 1; i++)
    {
        if (word[i] == '\0')
        {
            break;
        }

        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            total += word[i] + 32;
        }
        else
        {
            total += word[i];
        }
    }

    return total % N;
}