#include <cs50.h>
#include <stdio.h>
#include <math.h>

// prototypes
int coincount(int cents, int coin_value);
int coin_remain(int cents, int coin_value);

int main(void)
{
    // prompt user for change owed
    float input;
    do
    {
        printf("How much change is owed?:\n");
        input = GetFloat();
    }
    while (input < 0.0);
    
    // convert float into int in cents
    double clean_input = round(input * 100);
    int change = (int) clean_input;
    
    // analyze change, count coins, and pass remainder to same process with next coin
    int q_count = 0;
    int d_count = 0;
    int n_count = 0;
    int p_count = 0;
    if (change >= 25)
    {
        q_count = coincount(change, 25);
        change = coin_remain(change, 25);
    }
    if (change < 25 && change >=10)
    {
        d_count = coincount(change, 10);
        change = coin_remain(change, 10);
    }
    if (change < 10 && change >=5)
    {
        n_count = coincount(change, 5);
        change = coin_remain(change, 5);
    }
    if (change < 5)
    {
        p_count = change;
    }
    
    // calculate total number of coins and print
    int num_coin = q_count + d_count + n_count + p_count;
    printf("%i\n", num_coin);
}

// divides change by coin value and returns int of coins that can be divided into it
int coincount(int cents, int coin_value)
{
    return cents / coin_value;
}

// calculates and returns remainder of change leftover after coin value divided into change amount
int coin_remain(int cents, int coin_value)
{
    return cents % coin_value;
}