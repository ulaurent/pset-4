/* Recovering a deleted JPEG File */

#include <stdio.h>
#include <stdint.h>

int main (int argc, char *argv[])
{
    // if command line arguments does not equal 2 return an error
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover argument\n");
        return 1;
    }

    // set command line argument into variable
    char *raw_file = argv[1];

    // Open the file
    FILE *file = fopen (raw_file, "r");

    // Check if file open is not equal to NULL
    if (file == NULL)
    {
        fprintf(stderr, "File Not opened");
        return 2;
    }

    typedef uint8_t BYTE;
    BYTE buffer[512];
    FILE *image = NULL;
    // Used to store new filename names created using 'sprintf'
    char filename[8];
    // Image count increases to change jpeg filename each time
    int img_count = 0;

    // Now we want to read into file while it hasnt reached EOF (end of file)
    while (fread(buffer, 1, 512, file) == 512)
    {
        // If this condition passes, we know what we are reading into is a header of a Jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // When we hit a JPEGS header, we must start a new file,
            // To check if we are in an image file already created and open, we have to close it
            // before creating a new image file

            if (image != NULL) // We know if its not equal to null it is an open file with values in it so we must close the file
            {
                fclose(image);
            }

            // Now if it is equal to NULL we know the image hasnt been created yet
            // Now we want to write the block to an out put file called image
            // creating a new output file each go around

            // string print file name to store in a variable filename // img count changes file name each time
            sprintf(filename, "%03i.jpg", img_count);
            img_count ++;

            // Open up new image file created
            image = fopen(filename, "w");

            // Then write block to image file created
            fwrite(buffer, 1, 512, image);
        }

        // Else if its not a header of a JPEG file, we know we can just write it to the current image file open
        else
        {
            // If image is not equal to null we know it is an open file, so we can just write to it
            if (image != NULL)
            {
                fwrite(buffer, 1, 512, image);
            }
        }

    }


}