#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask user for input
    printf("Please provide an integer: ");
    int x = GetInt();
    printf("Please provide another integer: ");
    int y = GetInt();
    
    // do the math
    printf("The sum of %i and %i is %i!\n", x, y, x + y);
}