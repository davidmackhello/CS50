#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char* s = GetString();
    if (s == NULL)
    {
        return 1;
    }
    
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        printf("%c\n", *(s + i));
    }
}