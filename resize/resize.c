#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include "bmp.h"

int main (int argc, char *argv[]){

    if (argc != 4)
    {
        fprintf (stderr, "User: Command line only accepts three args.\n");
        return 1;
    }

    int n = (atoi)(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if( n > 100 && n % 2 != 0){

        fprintf(stderr, "User input: factor number parameters\n");
        return 2;
    }

    // Now try and open the file

    // open input file for reading
    FILE *inptr = fopen(infile, "r");

    // NULL is default value if file didnt open
    if(inptr == NULL){
        fprintf(stderr, "INFile not able to open\n");
        return 3;
    }

    // open output file for writing
    FILE *outptr = fopen(outfile, "w");

    if (outptr == NULL){

        fclose(inptr);
        fprintf(stderr, "OUTFILE not able to open\n");
        return 4;
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

    // We will probably have to revise the padding formula
    // determine padding for scanlines

    // Padding for infile
    int paddingIn = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    long initWidth = bi.biWidth;
    long initHeight = abs(bi.biHeight);

    bi.biWidth *= n;
    bi.biHeight *= n;

    // Padding for out-file
    int paddingOut = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + paddingOut) * labs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // Iterate over in-file's scanlines
    for (int i = 0; i < initHeight; i++)
    {
        // to write each row of pixels n times again
        for (int out_height = 0; out_height < n; out_height ++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < initWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // to write each pixel n times horizontally
                    for(int k = 1; k <= n; k++)
                        {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                        }
            }

            fseek(inptr, paddingIn, SEEK_CUR);

            fseek(inptr, -((initWidth * sizeof(RGBTRIPLE)) +paddingIn), SEEK_CUR);

            for (int k = 0; k < paddingOut; k++)
            {
                fputc(0x00, outptr);
            }

        }

        //Set cursor to the next line
        fseek(inptr, (initWidth * sizeof(RGBTRIPLE) + paddingIn), SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;

}