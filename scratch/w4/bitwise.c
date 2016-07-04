#include <stdio.h>

int main(void)
{
    int a = 1;
    int b = 2;
    printf("a is %i\n", a);
    printf("b is %i\n", b);
    printf("swapping...\n");    
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("a is %i\n", a);
    printf("b is %i\n", b);
}