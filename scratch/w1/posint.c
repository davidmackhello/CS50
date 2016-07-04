#include <cs50.h>
#include <stdio.h>

// prototype
int GetPosInt(void);

int main(void)
{
    int n = GetPosInt();
    printf("Thanks for the positive integer, which is %i, buddy!\n", n);
}

// demands positive int
int GetPosInt(void)
{
    int x;
    do
    {
        printf("Give me a positive integer, please: ");
        x = GetInt();
    }
    while (x < 1);
    return x;
}



























