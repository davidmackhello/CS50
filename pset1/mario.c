/**
 * mario.c
 * 
 * Builds mario half pyramid based on user input
 * 
 */

#include <cs50.h>
#include <stdio.h>

// prototype
void charprint(char c, int a);

int main(void)
{
    // defines blank and brick characters, and width of top of pyramid
    char blank = ' ';
    char brick = '#';
    int top = 2;
    
    // request height from user 
    int h;
    do
    {
        printf("Height: ");
        h = GetInt();
    }
    while (h < 0 || h > 23);
    
    /*
    
    // builds pyramid according to parameters
    for (int i = (h-1); i >= 0; i--, top++)
    {
        charprint(blank,i);
        charprint(brick,top);
        printf("\n");
    }
    
    */
    
    for (int i = 0; i < height; i++, height--, top++)
    {
        charprint(blank, (height-1));
        charprint(block, top);
        printf("\n");
    }
}

// function designed to print character 'c' a times
void charprint(char c, int a)
{
    for (int i = 0; i < a; i++)
    {
        printf("%c", c);
    }
}