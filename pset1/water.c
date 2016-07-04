/**
 * water.c
 * 
 * Generates equivalent water bottles used in user's shower habits
 * 
 */
 
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt user for shower time
    printf("minutes: ");
    int shower_time = GetInt();
    
    // use conversion factors to translate minutes to bottles
    int bottles = (shower_time * 1.5 * 128 / 16);
    
    // display output (number of bottles) to user
    printf("bottles: %i\n", bottles);
}