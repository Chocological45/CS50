// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 24;

// Hash table
node *table[N];


//Global variable counter for counting size of dictionary
int counter = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //hash word to obtain a hash value
    unsigned int h = hash(word);

    //access linked list at the index in the hash table
    node *cursor = table[h];

    //traverse linked list, looking for the word (strcasecmp)

    while (cursor != NULL)
    {
        //Compare case insensitive strings
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }
        else
        {
            //Move to cursor to next node
            cursor = cursor -> next;
        }
    }

    return false;
}




// Modified implementation of djb2 hash function, to accomodoate case insensitive strings
// ref: https://gist.github.com/MohamedTaha98/ccdf734f13299efb73ff0b12f7ce429f
// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;

    int c;

    //Find the lowercase hash value of word using djb2
    while ((c = *word++))
        hash = ((hash << 5) + hash) + tolower(c);

    return hash % N;
}





// Loads dictionary into memory, returning mtrue if successful else false
bool load(const char *dictionary)
{
    //Open dicitonary file
    FILE *dic = fopen(dictionary, "r");;

    //Check if file is valid
    if (dic == NULL)
    {
        //Unload the dictionary and end
        unload();
        return false;
    }

    //Initialize array for word
    char wrd[LENGTH + 1];

    //Initialize hash variable and temporary node
    node *tempn = NULL;
    //int h = 0;

    //Read strings from file one at a time
    while (fscanf(dic, "%s", wrd) != EOF)
    {
        //Creat a new node for each word
        node *n = malloc(sizeof(node));

        //check that memory has been allocated properly
        if (n == NULL)
        {
            return false;
        }

        //Copy input variable to node
        strcpy(n -> word, wrd);

        //Hash word to obtain a hash value
        int h = hash(wrd);

        //Insert node into hash table at that location
        tempn = n;
        tempn -> next = table[h];
        table[h] = tempn;
        counter++;
    }

    fclose(dic);

    return true;

}





// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //Return the counter value
    return counter;
}





// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //For all the nodes in the hash table
    for (int i = 0; i < N; i++)
    {
        //Setup a cursor node for the has table index node
        node *cursor = table[i];

        //Iterate through the hash table
        while (cursor != NULL)
        {
            //Traverse the hash table and free up all the memory
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
    }
    return true;
}
