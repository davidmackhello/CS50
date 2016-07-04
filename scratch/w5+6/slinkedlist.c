#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include "structs.h"

void print_last();
int add_beg(int number);
void print_all();
int destroy(node* list);
int insert_after_third();

// define global pointer to list
node* head = NULL;

int main(void)
{
    // add nodes according to user input
    printf("How many nodes would you like to add to the list?: ");
    int n = GetInt();
    int newval;
    for (int i = 0; i < n; i++)
    {
        printf("val%i: ", (i + 1));
        newval = GetInt();
        add_beg(newval);
    }
    
    for (int i = 0; i < 5; i++)
    {
        printf("*\n");
    }
    printf("Analyzing list...\n");
    for (int i = 0; i < 5; i++)
    {
        printf("*\n");
    }
    
    // print all nodes
    print_all();
    
    // print last node
    print_last();
    
    // insert after third and reanalyze
    insert_after_third();
    for (int i = 0; i < 5; i++)
    {
        printf("*\n");
    }
    printf("Analyzing list...\n");
    for (int i = 0; i < 5; i++)
    {
        printf("*\n");
    }
    print_all();
    print_last();
    
    // free all nodes
    if (head == NULL)
    {
        printf("The list is empty, and nothing can be freed.\n");
    }
    else
    {
        destroy(head);   
    }
}


// adds new node to beginning of list
int add_beg(int number)
{
    node* new = malloc(sizeof(node));
    if (new == NULL)
    {
        return 1;
    }
    
    // put int in new node
    new->val = number;
    
    // add first node if no list yet exists
    if (head == NULL)
    {
        head = new;
        new->next = NULL;
        printf("New list started with %i\n", number);
        return 0;
    }
    
    // add new node to beginning of existing list
    else
    {
        new->next = head;
        head = new;
        printf("Node containing %i added at beginning of list\n", number);
        return 0;
    }
}


// prints sll last node's value
void print_last()
{
    if (head == NULL)
    {
        printf("The list is empty; no last element.\n");
    }
    
    else
    {
        // declare traversal pointer
        node* crawler = head;
        
        // traverse until end of list
        while (crawler->next != NULL)
        {
            crawler = crawler->next;
        }
        
        // print final value    
        printf("The final element is %i\n", crawler->val);
    }
}

// prints int values for all nodes
void print_all()
{
    if (head == NULL)
    {
        printf("The list is empty.\n");
    }
    
    else
    {
        // declare traversal pointer
        node* crawler = head;
        int counter = 1;
        
        // traverse until end of list
        while (crawler != NULL)
        {
            printf("The integer at node %i is %i\n", counter, crawler->val);
            counter++;
            crawler = crawler->next;
        }
    }
}

// frees allocated memory for all nodes.
int destroy(node* list)
{
    if (list == NULL)
    {
        return 0;
    }
    
    else
    {
        destroy(list->next);
        free(list);   
        return 0;
    }
}

int insert_after_third()
{
    if (head == NULL)
    {
        printf("The list is empty; no third element.\n");
    }
    
    else
    {
        // declare traversal pointer and get int from user
        node* crawler = head;
        printf("Please give me an integer to insert after the 3rd element: ");
        int newval = GetInt();
    
        // set traversal pointer to 3rd element in list
        for (int i = 0; i < 2; i++)
        {
            if (crawler->next == NULL)
            {
                printf("List contains less than 3 elements\n");
                return 1;
            }
            
            else
            {
                crawler = crawler->next;
            }
        }
        
        // allocate new node, retrieve value from user, and insert node
        node* new = malloc(sizeof(node));
        if (new == NULL)
        {
            return 1;
        }
        new->val = newval;
        
        new->next = crawler->next;
        crawler->next = new;
    }
    return 0;
}