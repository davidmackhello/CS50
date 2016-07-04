#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask the user for an integer
    printf("Please choose an integer between 1 and 10: ");
    int x = GetInt();
    
    // judge user input
    if (x >= 1 && x <= 3)
    {
        printf("You picked a small number!\n");
    }
    else if (x >=4 && x <=7)
    {
        printf("You picked a medium number!\n");
    }
    else if (x >= 7 && x <=10)
    {
        printf("You picked a big number!\n");
    }
    else
    {
        printf("You did not pick an integer between 1 and 10.\n");
    }
}