#include <stdio.h>
#include <cs50.h>

// prototype
int fib(int n);

int main (int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fib i\n");
        return 1;
    }

    // ensure valid input
    int num = atoi(argv[1]);
    if (num < 0)
    {
        printf("no negative numbers brah\n");
        return 2;
    }
    
    //
    printf("Your Fibonacci number is  %i\n", fib(num));
}

int fib(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fib(n - 1) + fib(n - 2);
}