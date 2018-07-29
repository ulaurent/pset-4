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
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biWidth *= n;
    bi.biHeight *= n;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    // abs is the absolute value inorder to always return a psotive number
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // triple.rgbtBlue *= n;
            // triple.rgbtGreen *= n;
            // triple.rgbtRed *= n;

            // write RGB triple to outfile
            for(int k = 1; k <= n; k++){

            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

            }

        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;

}