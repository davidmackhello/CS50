#include <cs50.h>
#include <stdio.h>

// prototype
void cough(int n);

int main(void)
{
    // cough times specified by user
    printf("How many times would you like me to cough?: ");
    int hock = GetInt();
    cough(hock);
}

// cough n times
void cough(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("cough\n");
    }
}