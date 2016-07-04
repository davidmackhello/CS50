#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Enter your name, please: ");
    string name = GetString();
    printf("Hello, %s!\n", name);
}