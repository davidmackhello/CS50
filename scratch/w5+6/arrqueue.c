#include <stdio.h>
#include <cs50.h>
#include "structs.h"

#define CAPACITY 10

void enqueue(queue*, int);
void dequeue(queue*);

int main(void)
{
    queue q;
    q.size = 0;
    q.front = 0;
    int input;
    
    do
    {
        printf("What would you like to do (1.eq/2.dq/3.print/4.quit): ");
        input = GetInt();
        
        if (input == 1)
        {
            printf("What number would you like to add to the queue?: ");
            int num = GetInt();
            enqueue(&q, num);
        }
        
        if (input == 2)
        {
             dequeue(&q);
        }
        
        if (input == 3)
        {
            for (int i = 0; i < CAPACITY; i++)
            {
                printf("q.array[%i] is: %i\n", i, q.array[i]);
            }
            printf("q.front is %i\n", q.front);
            printf("q.size is %i\n", q.size);
        }
    }
    while (input != 4);
    printf("Goodbye.\n");
    return 0;
}

void enqueue(queue* qad, int val)
{
    if (qad->size < CAPACITY)
    {
        int addhere = (qad->front + qad->size) % CAPACITY;
        qad->array[addhere] = val;
        qad->size++;
    }
    
    else
        printf("The queue is full! Cannot add any more values.\n");
}

void dequeue(queue* qad)
{
    if (qad->size == 0 & qad->front == 0)
        printf("There is nothing to dequeue!\n");
        
    else
    {
        printf("You just pulled off %i\n", qad->array[qad->front]);
        qad->size--;
        qad->array[qad->front] = 9999;
        qad->front = (qad->front + 1) % CAPACITY;
    }
}