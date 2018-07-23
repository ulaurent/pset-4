#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main (int argc, char *argv[]){

    if (argc != 3){

        fprintf(stderr, "Usage: Error with command line arg. amounts");

        return 1;
    }

    // Name of input file to open for reading
    // & Nam eof output file to open for writing

    char *infile = argv[1];
    char *outfile = argv[2];

    // Now try to open input file using strings created above
    FILE *inptr = fopen(infile, "r");   // Maybe "r" meaning reader file

    if (inptr == NULL){

        fprintf(stderr, "Could not open %s.\n", infile);

        return 2;
    }


    // Now try to open output file using strings created above

    FILE *outptr = fopen(outfile, "w"); // Maybe "w" meaning writer file

    if (outptr == NULL){

        fclose(inptr);
        fprintf(stderr, "Could not open %s.\n", outfile);

        return 3;
    }




    // Area below is where I need to gain more understanding

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

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // File position indicator

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