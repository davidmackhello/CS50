#include <cs50.h>
#include <stdio.h>

// prototypes
void say(string word, int s);
void cough(int c);
void sneeze(int z);

// cough and sneeze at frequency according to user
int main(void)
{
    printf("How many times would you like me to cough?: ");
    int h = GetInt();
    printf("How many times would you like me to sneeze?: ");
    int e = GetInt();
    cough(h);
    sneeze(e);
}

// say string s times
void say(string word, int s)
{
    for (int i = 0; i < s; i++)
    {
        printf("%s\n", word);
    }
}

// cough c times via say function
void cough(int c)
{
    say("cough", c);
}

// sneeze z times via say function
void sneeze(int z)
{
    say("achoo!", z);
}