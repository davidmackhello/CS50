#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define ALPHASIZE 26
#define LOWBOUND_UPPERC 65
#define LOWBOUND_LOWERC 97

// prototype
char alphashift(char px, int shift);
int alpharef(char a);

int main(int argc, string argv[])
{
    // ensure correct command-line argument format
    if (argc != 2)
    {
        printf("Usage: vigenere <key>\n");
        return 1;
    }
    
    // verify key argv[1][i] contains only alphabetic characters
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("Key must be an alphabetic string.\n");
            return 1;
        }
    }
    
    // prompt user for plaintext and declare string length for plaintext and key
    string plaintext = GetString();
    int plainlen = strlen(plaintext);
    int keylen = strlen(argv[1]);
    
    // create array of shift values corresponding to plaintext string length for given vigenere key
    int shiftval[plainlen];
    for (int i = 0, t = 0; i < plainlen; i++, t++)
    {
        if (t > (keylen - 1))
        {
            t = 0;
        }
        shiftval[i] = alpharef(argv[1][t]);
    }
    
    // encrypt message according to shift vallues in shiftval array; only shifts letters
    for (int i = 0, j = 0; i < plainlen; i++, j++)
    {
        if (isalpha(plaintext[i]))
        {
           printf("%c", alphashift(plaintext[i], shiftval[j]));
        }
        else
        {
            printf("%c", alphashift(plaintext[i], 0));
            j = j - 1;
        }
    }
    printf("\n");
}

// shifts alphabetical values according to specified key for uppercase and lowercase letters, given starting char px
char alphashift(char px, int shift)
{
    // ensures shift on alphabetical input only
    if (isalpha(px) == false)
    {
        return px;
    }
    
    // calculates shift and positional values
    int k = shift % ALPHASIZE;
    int rawsum = (int) px + k;
    
    // returns new position for uppercase and lowercase values
    if (px >= 'A' && px <= 'Z' && (rawsum > (LOWBOUND_UPPERC + ALPHASIZE - 1)))
    {
        return (char) ((int) px + k - ALPHASIZE);
    }
    else if (px >= 'a' && px <= 'z' && (rawsum > (LOWBOUND_LOWERC + ALPHASIZE - 1)))
    {
        return (char) ((int) px + k - ALPHASIZE);
    }
    else
    {
        return (char) rawsum;
    }
}

// provides reference number for vigenere key so that 'A' and 'a' are 0 and 'Z' and 'z' are 25
int alpharef(char a)
{
    if (a >= 'A' && a <= 'Z')
    {
        return ((int) a - LOWBOUND_UPPERC);
    }
    else if (a >= 'a' && a <= 'z')
    {
        return ((int) a - LOWBOUND_LOWERC);
    }
    else
    {
        return 0;
    }
}