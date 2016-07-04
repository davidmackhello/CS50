#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Say Something: ");
    string s = GetString();
    
    printf("Say something: ");
    string t = GetString();
    
    if (s == t)
    {
        printf("You typed the same thing dummy!\n");
    }
    else
    {
         printf("You typed something different!\n");
    }
}