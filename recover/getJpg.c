/* Program to fins out how many photos in deleted raw file*/

#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    if (argc == 2)
    {
        char *file = argv[1];

        FILE *card = fopen(file, "r");

        if (!card)
        {
            printf("No file or nothing in file\n");
            fclose(card);
            return 1;
        }
        // Define buffer

        unsigned char buffer[512];

        // keep count of images

        int imgcount = 0;

        while(fread(buffer, 512, 1, card) == 1)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                imgcount ++;
            }
        }

        printf("Total num img files: %i\n", imgcount);
        fclose(card);
        return 0;
    }

    else
    {
        printf("Usage: ./getJpg filename");
        return 2;
    }
}