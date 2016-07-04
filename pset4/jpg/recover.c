/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>
#include <cs50.h>

// define camera card's block size in bytes
#define CAMBLOCK 512

// prototypes
bool isjpeg(uint8_t* buffer);

int main(void)
{
    // open card.raw file
    FILE* cardfile = fopen("card.raw", "r");
    if (cardfile == NULL)
    {
        printf("Could not open card.raw");
        return 1;
    }
    
    // create buffer to hold each block of card data
    uint8_t* buffer = malloc(CAMBLOCK * sizeof(uint8_t));
    if (buffer == NULL)
    {
        return 2;
    }

    // create char array and counter variables for naming jpeg files
    char jpg_name[8];
    int jcount1 = 0;
    int jcount2 = 0;

    // read through each block, checking for jpeg signature
    while (fread(buffer, CAMBLOCK, 1, cardfile) == 1)
    {
        if (isjpeg(buffer))
        {
            // assign appropriate jpeg filename to string
            sprintf(jpg_name, "0%d%d.jpg", jcount1, jcount2);

            // create new jpg file
            FILE* jpg_out = fopen(jpg_name, "w");
            if (jpg_out == NULL)
            {
                fclose(cardfile);
                return 2;
            }
            
            do
            {
                // write blocks to outfile
                fwrite(buffer, CAMBLOCK, 1, jpg_out);
                
                // continue reading into cardfile and writing to output until next jpeg signature, ending program if EOF is reached
                while (fread(buffer, CAMBLOCK, 1, cardfile) != 1)
                {
                    fclose(cardfile);
                    fclose(jpg_out);
                    free(buffer);
                    return 0;
                }
            } while (!isjpeg(buffer));
            
            // close jpg output file
            fclose(jpg_out);
            
            // advance counter variables
            jcount2++;
            if (jcount2 > 9)
            {
                jcount1++;
                jcount2 = 0;
            }
            
            // seek back one block to re-read current jpeg header
            fseek(cardfile, -CAMBLOCK, SEEK_CUR);
        }
    }
}

// determine if current block has jpeg signature in first four bytes
bool isjpeg(uint8_t* buffer)
{
    if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] >= 0xe0) && (buffer[3] <= 0xef))
    {
        return true;
    }
    else
    {
        return false;
    }
}