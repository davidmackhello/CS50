#include <stdio.h>
#include <cs50.h>
#include "structs.h"

queuel* enqueue(queuel*, int);
queuel* dequeue(queuel*);
void printall(queuel*);
int destroy(queuel*);



int main(void)
{
    // define pointer to top of stack
    queuel* fqueue = NULL;
    
    // let user choose action
    int input;
    do
    {
        printf("What would you like to do (1.eq/2.dq/3.print/4.quit): ");
        input = GetInt();
        
        // enqueue values at end of singly linked list
        if (input == 1)
        {
            printf("What number would you like to add to the queue?: ");
            int num = GetInt();
            fqueue = enqueue(fqueue, num);
        }
        
        // dequeue values from head of singly linked list
        if (input == 2)
        {
             fqueue = dequeue(fqueue);
        }
    
        if (input == 3)
        {
           printall(fqueue);
        }
    }
    while (input != 4);
    
    // free all nodes
    if (fqueue == NULL)
    {
        printf("The list is empty, and nothing can be freed.\n");
    }
    else
    {
        destroy(fqueue);   
    }
    printf("Goodbye.\n");
    return 0;
}


queuel* enqueue(queuel* top, int newval)
{
    queuel* new = malloc(sizeof(queuel));
    if (new == NULL)
        return NULL;
    
    // set val and next pointer for new element
    new->val = newval;
    new->next = NULL;    
    
    // add first element if no queue exists
    if (top == NULL)
    {
        printf("New list started with %i\n", newval);
        return new;
    }
    
    // add new element to end of existing queue
    else
    {
        queuel* trav = top;
        while (trav->next != NULL)
        {
            trav = trav->next;
        }
        
        trav->next = new;
        return top;
    }
    
}

void printall(queuel* top)
{
    // check if queue exists
    if (top == NULL)
    {
        printf("The queue is empty.\n");
    }
    
    // declare traversal pointer
    queuel* trav = top;
    
    // traverse list and print values
    int counter = 1;
    while (trav != NULL)
    {
        printf("The value of queue element %i is %i\n", counter, trav->val);
        counter++;
        trav = trav->next;
    }
}

queuel* dequeue(queuel* top)
{
    // check if queue exists
    if (top == NULL)
    {
        printf("The queue is empty.\n");
    }
    
    // print first queue element and update stack structure
    queuel* del = top;
    printf("The earliest element of the queue was %i\n", top->val);
    top = top->next;
    free(del);
    return top;
}

int destroy(queuel* top)
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