#include <cs50.h>
#include <stdio.h>

// prototype
void cough(void);

int main(void)
{
    // cough 3x
    for (int i = 0; i < 3; i++)
    {
        cough();
    }
}

void cough(void)
{
    // say "cough"
    printf("cough\n");
}