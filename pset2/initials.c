#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string name = GetString();
    printf("%c", toupper(name[0]));
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if (name[i] == ' ' && i != (n-1))
        {
            printf("%c", toupper(name[i+1]));
        }
    }
    printf("\n");
}