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
   if (a <= 0)
   {
       return 0;
   }
   
   else
   {
       return (a + sigma (a - 1));
   }
}