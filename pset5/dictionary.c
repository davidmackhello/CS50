/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * 
 * This program uses the hash function djb2, developed by Dan Bernstein, with implementation modeled after that found at http://stackoverflow.com/questions/10696223/reason-for-5381-number-in-djb-hash-function
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// prototypes
unsigned int hash(char* str, unsigned int len);
node* addnode(node* newguy, node* head);
int destroy(node* head);

// declare global variable for dictionary size
int wcount = 0;

// declare global hash table array of pointers to singly-linked list nodes
node* table[TABLESIZE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // create and fill buffer for all-lowercase version of queried word
    char lword[LENGTH + 1];
    unsigned int j = strlen(word);
    for (int i = 0; i <= j; i++)
    {
        lword[i] = tolower(word[i]);
    }
    
    // hash queried word
    unsigned int hashval = hash(lword, j);
    
    // if no list exists at hash table array, word is not in dictionary
    if (table[hashval] == NULL)
    {
        return false;
    }
    
    else
    {
        // declare traversal pointer
        node* trav = table[hashval];
        
        // traverse list to check word against each node
        while (trav != NULL)
        {
            // compare queried string to current node, returning true if word found
            if (strcmp(lword, trav->word) == 0)
            {
                return true;
            }
            
            // move to next node
            else
            {
                trav = trav->next;
            }
        }
        
        // if traversal pointer makes it to end of list, word is not present
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // opens dictionary file
    FILE* dict = fopen(dictionary, "r"); 
    if (dict == NULL)
    {
        return false;
    }
    
    // set all pointers in hash table array to NULL
    for (int i = 0; i < TABLESIZE; i++)
    {
        table[i] = NULL;
    }
    
    // create temp unsigned int for hash values
    unsigned int hashval;

    while (true)
    {
        // allocate new node for word
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        
        // load word from dictionary into node
        if (fscanf(dict, "%s", new_node->word) == 1)
        {
            // obtain hash value for string
            hashval = hash(new_node->word, strlen(new_node->word));
        
            // add new node to linked list at appropriate hash table array element
            table[hashval] = addnode(new_node, table[hashval]);
            
            // increment word counter
            wcount++;
        }
        
        // if end of dictionary file reached, free current empty node, and close dictionary
        else
        {
            free(new_node);
            fclose(dict);
            return true;
        }
    }
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // returns global counter tabulated with load function
    return wcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // call destroy function on each linked list in hash table array
    for (int i = 0; i < TABLESIZE; i++)
    {
        destroy(table[i]);
    }
    return true;
}

// djb2 hash function (implementation modeled after http://stackoverflow.com/questions/10696223/reason-for-5381-number-in-djb-hash-function)
unsigned int hash(char* str, unsigned int len)
{
   unsigned int hash = 5381;
   unsigned int i = 0;

   for(i = 0; i < len; str++, i++)
   {   
      hash = ((hash << 5) + hash) + (*str);
   }   

   return hash % TABLESIZE;
}

// adds new node to beginning of list
node* addnode(node* newguy, node* head)
{
    // add to head of list if no list yet exists
    if (head == NULL)
    {
        newguy->next = NULL;
        return newguy;
    }
    
    // else add new node to beginning of existing list
    else
    {
        newguy->next = head;
        return newguy;
    }
}

// frees allocated memory for all nodes in linked list
int destroy(node* head)
{
    // returns 0 if no linked list exists; also serves as base case for destroy function
    if (head == NULL)
    {
        return 0;
    }
    
    else
    {
        destroy(head->next);
        free(head);   
        return 0;
    }
}