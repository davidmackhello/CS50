#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    printf("Say Something: ");
    char* s = GetString();
    
    printf("Say something: ");
    char* t = GetString();
    
    // compare strings
    if (s != NULL && t != NULL)
    {
        if (strcmp(s, t) == 0)
        {
            printf("You typed the same thing!\n");
        }
        else
        {
            printf("You typed different things!\n");
        }
    }
}