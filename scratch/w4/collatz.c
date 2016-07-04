#include <stdio.h>
#include <cs50.h>

// prototype
int collatz(int n);

int main (int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: collatz i\n");
        return 1;
    }

    // ensure valid input
    int num = atoi(argv[1]);
    if (num < 1)
    {
        printf("no negative numbers brah\n");
        return 2;
    }
    
    //
    printf("Number of collatz steps: %i\n", collatz(num));
}

int collatz(int n)
{
    if (n == 1)
        return 0;    
    else if (n % 2 == 0)
        return 1 + collatz(n / 2);
    else
        return 1 + collatz((3 * n) + 1);
}