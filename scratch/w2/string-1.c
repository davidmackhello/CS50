#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // get string
    printf("May I have a string please?: ");
    string s = GetString();
    
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c\n", s[i]);
    }
}