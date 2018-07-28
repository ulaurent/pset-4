#include <stdio.h>
#include <cs50.h>

#include "bmp.h"

int main (int argc, char *argv[]){

    if (argc != 3)
    {
        fprintf (stderr, "User: Command line only accepts three args.\n");
        return 1;
    }

    int n = (int)(argv[0] - '0');
    char *infile = argv[1];
    char *outfile = argv[2];

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



}