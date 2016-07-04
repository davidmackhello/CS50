/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP piece by piece.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // ensure n is between 1 and 100 inclusive
    int n = atoi(argv[1]);
    if (n < 1 || n > 100)
    {
        printf("n must be a positive integer less than or equal to 100\n");
        return 5;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // declare new structs for outfile's headers
    BITMAPFILEHEADER bf_o = bf;
    BITMAPINFOHEADER bi_o = bi;
    
    // update BITMAPINFOHEADER parameters and calculate total padding needed for outfile
    bi_o.biWidth = bi.biWidth * n;
    bi_o.biHeight = bi_o.biHeight * n;
    int padding_t = ((4 - (bi_o.biWidth * sizeof(RGBTRIPLE)) % 4) % 4) * abs(bi_o.biHeight);
    bi_o.biSizeImage = bi_o.biWidth * abs(bi_o.biHeight) * sizeof(RGBTRIPLE) + padding_t;

    // update parameters of outfile's BITMAPFILEHEADER
    bf_o.bfSize = bi_o.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_o, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_o, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for infile and outfile scanlines
    int padding_i = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_o = (4 - (bi_o.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    RGBTRIPLE row[bi_o.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in infile scanline
        for (int j = 0, l = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // expand image horizontally
            for (int k = 0; k < n; k++, l++)
            {
                row[l] = triple;
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
            // skip over padding of infile, if any
            fseek(inptr, padding_i, SEEK_CUR);
            
            // write padding to outfile scanline
            for (int m = 0; m < padding_o; m++)
            {
                fputc(0x00, outptr);
            }
            
            // expand image vertically by re-printing identical rows
            for (int o = 0; o < (n - 1); o++)
            {
                for (int p = 0; p < bi_o.biWidth; p++)
                {
                    fwrite(&row[p], sizeof(RGBTRIPLE), 1, outptr);
                }
                
                // write padding to outfile scanline
                for (int m = 0; m < padding_o; m++)
                {
                    fputc(0x00, outptr);
                }
            }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}