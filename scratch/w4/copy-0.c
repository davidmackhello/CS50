/**
 * copy-0.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Tries and fails to copy two strings.
 *
 * Demonstrates strings as pointers to arrays.
 */
       
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
    
    // try (and fail) to copy string
    char* t = s;
 
    // change "copy"
    printf("Capitalizing copy...\n");
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    // print original and "copy"
    printf("Original: %s\n", s);
    printf("Copy:     %s\n", t);

    // success
    return 0;
}