// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <strings.h> // for strcasecmp() fun.
#include <string.h>  // for strcpy()  fun.
#include <ctype.h>  // for toupper()  fun.
#include <stdlib.h> // for free()  fun.

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 26;

// Hash table size 26 (0-25)
struct node *table[N];

// Counter array for each hash element node size
int counter[N] = {0};

// Check the word and return bool
bool check(const char *word)
{
    int bucket = hash(word);
    node *curser = table[bucket];

    for (int i = 0; i < counter[bucket]; i++)
    {
        if (strcasecmp(curser->word, word) == 0)
        {
            return true;
        }
        else
        {
            curser = curser->next;
        }
    }
    return false;
}

// Hash function which return (sum of each all ascii char % 26) Bucket index
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        sum += toupper(word[i]);
    }
    return sum % N;
}

// Load the word from dictionary to the Hash table
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");
    char word[LENGTH+1];
    int bucket;

    if (dic == NULL)
    {
        return false;
    }

    while (fscanf(dic, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("full memory");
            unload();
            return false;
        }

        strcpy(new_node->word, word);
        new_node->next = NULL;

        bucket = hash(new_node->word);

        if (bucket < 26)
        {
            if (table[bucket] == NULL)
            {
                table[bucket] = new_node;
                counter[bucket] = 1;
            }
            else
            {
                new_node->next = table[bucket];
                table[bucket] = new_node;
                counter[bucket]++;
            }
        }
    }
    fclose(dic);
    return true;
}

// Return sum of counter[] global array which contains the each hash array element node count
unsigned int size(void)
{
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += counter[i];
    }
    return sum;
}

// Unload the all allocated memory by malloc() using free()
bool unload(void)
{
    node *curser;
    node *temp;

    for (int i = 0; i < N; i++)
    {
        temp = curser = table[i];
        while (curser != NULL)
        {
            curser = curser->next;
            free(temp);
            temp = curser;
        }
    }
    return true;
}
