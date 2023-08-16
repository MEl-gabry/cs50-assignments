// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 19683;

// Hash table
node *table[N];

int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *cur_node = table[index];
    while (cur_node != NULL)
    {
        if (strcasecmp(cur_node->word, word) == 0)
        {
            return true;
        }
        cur_node = cur_node->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = 0;
    int matches = 0;
    char *word_copy = malloc(strlen(word) + 1);
    for (int letter = 0, length = strlen(word); letter <= length; letter++)
    {
        word_copy[letter] = tolower(word[letter]);
    }
    for (int i = 0; i < 27; i++)
        {
            if (word_copy[0] == i + 97 || word_copy[0] == i + 13)
            {
                index += 729 * i;
                matches++;
            }
            if (word_copy[1] == i + 97 || word_copy[1] == i + 13)
            {
                index += 27 * i;
                matches++;
            }
            if (word_copy[2] == i + 97 || word_copy[2] == i + 13)
            {
                index += i;
                matches++;
            }
            if (matches == 3)
            {
                break;
            }
        }
    free(word_copy);
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }
    while (fscanf(dic, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        int index = hash(word);
        n->next = table[index];
        table[index] = n;
        words++;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cur_node = table[i];
        node *tmp = table[i];
        while (tmp != NULL)
        {
            cur_node = cur_node->next;
            free(tmp);
            tmp = cur_node;
        }
    }
    return true;
}