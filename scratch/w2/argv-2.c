#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0, l = strlen(argv[i]); j < l; j++)
        {
            printf("%c\n", argv[i][j]);
        }
        printf("\n");
    }
}