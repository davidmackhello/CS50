#include <cs50.h>
#include <stdio.h>

// prototype
int cube(int c);

int main(void)
{
    // Walk through cubing of x
    printf("What value would you like to cube?: ");
    int x = GetInt();
    printf("Your value is %i.\n", x);
    printf("Cubing....\n");
    int y = cube(x);
    printf("Cubed!\n");
    printf("The value of %i cubed is %i\n", x, y);
}

// cube value c
int cube(int c)
{
    return c * c * c;
}