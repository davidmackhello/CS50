#include <stdio.h>
#include <cs50.h>
#include "structs.h"

#define CAPACITY 10

void push(stack*, int);
int pop(stack*);

int main(void)
{
    stack s;
    s.top = 0;
    
    printf("How many values would you like to add to stack s?: ");
    int n = GetInt();
    int num;
    for (int i = 0; i < n; i++)
    {
        printf("What value would you like to add to the stack?: ");
        num = GetInt();
        push(&s, num);
    }
    
    printf("*\n");
    printf("Stack stacked! s.top is %i\n", s.top);
    printf("*\n");
    
    printf("How many values would you like to pop off the stack?: ");
    n = GetInt();
    
    if (n <= s.top)
    {
        for (int i = 0; i < n; i++)
        {
            printf("Popped %i\n", pop(&s));
        }
    }
    
    else
    {
        printf("Requested pops exceed stack size. Popping entire stack...\n");
        for (int i = 0, j = s.top; i < j; i++)
        {
            printf("Popped %i\n", pop(&s));
        }
    }
}

void push(stack* sad, int val)
{
    if (sad->top < CAPACITY)
    {
        sad->array[sad->top] = val;
        sad->top++;
    }
    
    else
        printf("This stack is full! Cannot push any more values.\n");
}

int pop(stack* sad)
{
    int val;
    {
        val = sad->array[(sad->top - 1)];
        sad->top--;
        return val;
    }
}