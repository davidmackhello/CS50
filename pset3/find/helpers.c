/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

// prototype for binary search function
bool binarysearch(int target, int sortedarray[], int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // returns false if n is not a positive integer
    if (n < 1)
    {
        return false;
    }
    
    // convert array size to starting minimum and maximum parameters for array
    int minimum = 0;
    int maximum = (n - 1);
    
    // call binarysearch function
    if (binarysearch(value, values, minimum, maximum))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Sorts array of n values with bubble sort.
 */
void sort(int values[], int n)
{
    // sets swap counter to non-zero int and creates temporary integer holder for swapping values
    int swap = -1;
    int temp;
    
    // runs bubble sort when swap counter is non-zero after completing each pass
    while (swap != 0)
    {
        swap = 0;
        
        // iterates through through array to the penultimate element
        for (int i = 0; i < (n-1); i++)
        {
            
            // compares each element to its neighbor, swaps and adds 1 to swap counter for out-of-order pairs
            if (values[i] > values[i+1])
            {
                temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
                swap++;
            }
        }
        // narrows bubble sort range to unsorted region after each pass 
        n--;
    }
    return;
}

/**
 * Searches sorted array using binary search
 */
bool binarysearch(int target, int sortedarray[], int min, int max)
{
    while (max >= min)
    {
        int midpoint = (min + max) / 2;
        
        if (target == sortedarray[midpoint])
        {
            return true;
        }
        
        else if (target > sortedarray[midpoint])
        {
           min = (midpoint + 1);
           binarysearch(target, sortedarray, min, max);
        }
        else if (target < sortedarray[midpoint])
        {
            max = (midpoint - 1);
            binarysearch(target, sortedarray, min, max);
        }
    }
    return false;
}