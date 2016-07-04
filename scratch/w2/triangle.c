#include <stdio.h>
#include <cs50.h>

bool valid_triangle(int a, int b, int c);

int main(void)
{
    printf("side 1: ");
    int a = GetInt();
    printf("side 2: ");
    int b = GetInt();
    printf("side 3: ");
    int c = GetInt();
    
    if (valid_triangle(a, b, c))
    {
        printf("good boy\n");
    }
    else
    {
        printf("bad boy\n");
    }
}

bool valid_triangle(int a, int b, int c)
{
    if (a > 0 && b > 0 && c > 0 && (a + b) > c && (b + c) > a && (a + c) > b)
    {
        return true;
    }
    else
    {
        return false;
    }
}