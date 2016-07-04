#include <stdio.h>
#include <cs50.h>
#include "structs.h"

stackl* push(stackl* top, int newval);
void printall(stackl* top);
int destroy(stackl* top);
stackl* pop(stackl* top);

// define global pointer to top of stack
stackl* fstack = NULL;

int main(void)
{
    // add values to stack according user input.
    printf("How many values would you like to add to 1stack?: ");
    int n = GetInt();
    int num;
    for (int i = 0; i < n; i++)
    {
        printf("What value would you like to add to the stack?: ");
        num = GetInt();
        fstack = push(fstack, num);
    }

    // print list
    printf("*\n*\n*\nAnalyizing list...\n*\n*\n*\n");
    printall(fstack);
    
    // pop values from stack according to user input
    printf("How many values would you like to pop from the stack?: ");
    n = GetInt();
    for (int i = 0; i < n; i++)
    {
        fstack = pop(fstack);
    }
    
    // print list
    printf("*\n*\n*\nAnalyizing list...\n*\n*\n*\n");
    printall(fstack);
    
    // free all nodes
    if (fstack == NULL)
    {
        printf("The list is empty, and nothing can be freed.\n");
    }
    else
    {
        destroy(fstack);   
    }
}



stackl* push(stackl* top, int newval)
{
    // allocate new stack element for top of list.
    stackl* new = malloc(sizeof(stackl));
    if (new == NULL)
    {
        return NULL;
    }
    
    // put int in new stack element
    new->val = newval;
    
    // add first element if no list yet exists
    if (top == NULL)
    {
        new->next = NULL;
        printf("New list started with %i\n", newval);
        return new;
    }
    
    // add element to top of existing stack
    else
    {
        new->next = top;
        printf("Node containing %i added at beginning of list\n", newval);
        return new;
    }
}

void printall(stackl* top)
{
    // check if stack exists
    if (top == NULL)
    {
        printf("The stack is empty.\n");
    }
    
    // declare traversal pointer
    stackl* trav = top;
    
    // traverse list and print values
    int counter = 1;
    while (trav != NULL)
    {
        printf("The value at stack element %i is %i\n", counter, trav->val);
        counter++;
        trav = trav->next;
    }
}

stackl* pop(stackl* top)
{
    // check if stack exists
    if (top == NULL)
    {
        printf("The stack is empty.\n");
    }
    
    // print top stack element and update stack structure
    stackl* del = top;
    printf("The top element of the stack was %i\n", top->val);
    top = top->next;
    free(del);
    return top;
}

int destroy(stackl* top)
{
    if (top == NULL)
    {
        return 0;
    }
    
    else
    {
        destroy(top->next);
        free(top);
        return 0;
    }
}