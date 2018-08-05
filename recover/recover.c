/* Program used to recover deleted jpeg files */

#include <stdint.h>
#include <stdio.h>


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover filename\ns");
    }

    //Get file from command line args
    char *raw_file = argv[1];

    // open input file
    FILE *file = fopen(raw_file, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", file1);
        return 1;
    }

    //BYTE type is used to create a BYTE array
    typedef uint8_t BYTE;
    BYTE buffer[512];
    FILE *img = NULL;
    int img_counter = 0;

    // Remember that filename is a string with 7 characters
    char filename[8];

    // If fread returns a value that is not 512, it signifies EOF
    while (fread(&buffer, 1, 512, file) == 512)
    {
        // Check for JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If header exists, check if a photo has been found yet
            if (img != NULL)
            {
                // If a photo was already found, close it before writing a new jpg file
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", img_counter);
            img_counter++;
            img = fopen(filename, "w");
            fwrite(buffer, 1, 512, img);
        }
        // If no header is read in this block, then write it to the current jpg
        else
        {
            //  Make sure we have opened a file already
            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }
}