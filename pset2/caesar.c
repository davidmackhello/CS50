#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define ALPHASIZE 26
#define UPPERSTART 65
#define LOWERSTART 97

// prototype
char alphamath(int lowbound, char px, int shift);

int main(int argc, string argv[])
{
    // ensure correct command-line entry
    if (argc != 2)
    {
        printf("Usage: caesar <key>\n");
        return 1;
    }
    
    // convert string k to integer
    int k = atoi(argv[1]);
    
    // verify k is a non-negative integer
    if (k < 0)
    {
        printf("Key must be a non-negative integer.\n");
        return 2;
    }
        
    // prompt user for string
    string plaintext = GetString();
    
    // index through each char in plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // only shift alphabetical characters
        if (isalpha(plaintext[i]))
        {
            // set AASCI starting point based on capitalization, calculate and print shifted char
            int lowbound = (isupper(plaintext[i])) ? UPPERSTART : LOWERSTART;
            printf("%c", alphamath(lowbound, plaintext[i], k));
        }
        
        // print non-alpha characters as is
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}

// calculates final position on alphabetical number line for a reference lower boundary, starting position px, and shift value
// handles wrapping and modular shift values greater than alphabet size
char alphamath(int lowbound, char px, int shift)
{
    int k = shift % ALPHASIZE;
    int rawsum = (int) px + k;
    if (rawsum > (lowbound + ALPHASIZE - 1))
    {
        return (char) ((int) px + k - ALPHASIZE);
    }
    else
    {
        return (char) rawsum;
    }
}