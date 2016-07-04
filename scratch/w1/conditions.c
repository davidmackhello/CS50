#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask for an integer
    printf("Please provide an integer: ");
    int x = GetInt();
    
    // analyze input
    if (x > 0)
    {
        printf("Your integer is positive!\n");
    }
    else if (x == 0)
    {
        printf("You chose zero! Nice!\n");
    }
    else
    {
        printf("Your integer is negative!\n");
    }
}