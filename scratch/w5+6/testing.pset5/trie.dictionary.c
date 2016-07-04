/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// declare global pointer to root of dictionary trie
node* root = NULL;

// declare global variable for dictionary size
int wcount = 0;

// prototype
int destroy(node* triep);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // create temp int for mapping within trie nodes and traversal pointer
    int index;
    node* trav = root;
    
    // determine if word is stored in trie
    for (int i = 0, j = strlen(word); i < j; i++)
    {
        // assign index path for each char
        if (word[i] == '\'')
        {
            index = ALPHASIZE - 1;
        }
        else
        {
            index = tolower(word[i]) - 'a';
        }
        
        // if path exists in trie, push traversal pointer to next node
        if (trav->children[index] != NULL)
        {
            trav = trav->children[index];
        }
        
        // if path does not exist, word is not in dictionary
        else
        {
            return false;
        }
    }
    
    // check boolean at end of path to see if word is stored in dictionary
    return trav->in_dict;
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
    
    // allocate root node and set pointer to it
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    
    // set all children pointers in root node to NULL and boolean to false
    for (int i = 0; i < ALPHASIZE; i++)
    {
        root->children[i] = NULL;
    }
    
    root->in_dict = false;
    
    // prepare buffer for each word read in from dictionary file 
    // create temp int for mapping within trie nodes and traversal pointer
    char dbuffer[LENGTH];
    int index;
    node* trav = root;

    // load words from dictionary, one at a time, into a buffer
    while (fscanf(dict, "%s", dbuffer) == 1)
    {
        // build trie path based on word in buffer
        for (int i = 0, j = (strlen(dbuffer)); i < j; i++)
        {
            // assign index path for each char
            if (dbuffer[i] == '\'')
            {
                index = ALPHASIZE - 1;
            }
            else
            {
                index = dbuffer[i] - 'a';
            }
            
            // if path exists in trie, push traversal pointer to next node
            if (trav->children[index] != NULL)
            {
                trav = trav->children[index];
            }
            
            // if path does not exist, create it
            else
            {
                trav->children[index] = malloc(sizeof(node));
                if (trav->children[index] == NULL)
                {
                    return false;
                }
                
                // advance traversal pointer to new node and set children to NULL and boolean to false
                trav = trav->children[index];
                
                for (int k = 0; k < ALPHASIZE; k++)
                {
                    trav->children[k] = NULL;
                }
                
                trav->in_dict = false;
            }
        }
        
        // assign boolean to true at end of path to denote properly loaded word
        // increment word dictionary size and return traversal pointer to root
        trav->in_dict = true;
        wcount++;
        trav = root;
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // check if trie exists
    if (root == NULL)
    {
        return false;
    }
    
    // call destroy function to free all nodes
    else
    {
        destroy(root);
        
        // reset word count
        wcount = 0;
        
        return true;
    }
}

/**
 * Frees allocated memory for all nodes within trie
 */
int destroy(node* triep)
{
    if (triep == NULL)
    {
        return 0;
    }
    
    else
    {
        for (int i = 0; i < ALPHASIZE; i++)
        {
            destroy(triep->children[i]);
        }
        free(triep);
        return 0;
    }
}
