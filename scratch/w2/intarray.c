#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int iarray[100];
    
    for (int i = 0; i < 100; i++)
    {
        iarray[i] = i;
    }
    
    for (int i = 0; i < 100; i++)
    {
        printf("%i\n", iarray[i]);
    }
}