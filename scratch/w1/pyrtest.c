#include <cs50.h>
#include <stdio.h>

// prototype
void charprint(char c, int a);

// prompt user
int main(void)
{
    char test = 'a';
    charprint(test, 10);
}


void charprint(char c, int a)
{
    for (int i = 0; i < a; i++)
    {
        printf("%c", c);
    }
    printf("\n");
}