#include <stdio.h>
#include <cs50.h>

int sigma(int a);

int main(void)
{
    int n;
    do
    {
        printf("Positive int please: \n");
        n = GetInt();
    }
    while (n < 1);
    
    int answer = sigma(n);
    printf("%i\n", answer);
}

int sigma(int a)
{
    int sum = 0;
    for(int i = 1; i <= a; i++)
    {
        sum += i;
    }
    return sum;
}