#include <stdio.h>
#include <cs50.h>

// prototype
int fact(int n);

int main (void)
{
    // get a positive integer from user
    int num;
    do
    {
        printf("Provide a positive int please: ");
        num = GetInt();    
    }
    while (num < 1);
    
    printf("The factorial of your number is %i\n", fact(num));
}

int fact(int n)
{
    if (n == 1)
        return 1;
    else
        return n * fact(n - 1);
}