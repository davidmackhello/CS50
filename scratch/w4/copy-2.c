#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    printf("Say something: ");
    char* s = GetString();
    if (s == NULL)
    {
        return 1;
    }
    
    // allocate memory
    char* t = malloc((strlen(s) + 1) * sizeof(char));
    
    // copy string
    for (int i = 0, l = strlen(s); i <= l; i++)
    {
        *(t + i) = *(s + i);
    }

    printf("Capitalizing copy...\n");
    
    if (strlen(t) > 0)
    {
        *t = toupper(*t);
    }

    // print original and "copy"
    printf("Original: %s\n", s);
    printf("Copy:     %s\n", t);

    // success
    return 0;
}