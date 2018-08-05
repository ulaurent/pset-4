/*program used to recover deleted jpeg files*/

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

int main (int argc, char *argv[]){

    if (argc != 2)

    {
        fprintf(stderr, "User: Check number of arguments\n");
    }

    return 1;

    char *inphotofile = argv[1];

    FILE *raw_file = fopen(inphotofile, "r");

    if(inphotofile == NULL)

    {
        fprintf(stderr, "User: file could not open");
        return 2;
    }

    typedef uint8_t BYTE;
    BYTE buffer[512];
    FILE *img = NULL;
    char *filename;
    int img_count = 0;


    // fread the raw_file only while a block is equal to 512, if its not equal to 512, thats the end of the file
   while(fread(buffer, 1, 512, raw_file) == 512) {

       if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 )
        {
            // If all this passes to be true, you hit the beginning of a new JPEG
            printf("true: new jpeg photo");

            //Now write to new file
            // If you hit a header && the file img is not equal to NULL, you know that your hitting a new file
            if(img != NULL)
            {
                fclose (img);
            }

            // string print stores in a string of char's called 'filename'
            // imgcount increases the count of the name of the file so it can save a new file each time
            sprintf(filename, "%03i.jpg", img_count); // creates filename for new jpeg and stores in filename variable
            img_count ++;
            // fopen the image
            img = fopen(filename, "w"); // opens the new file created to write

            fwrite(buffer, 1, 512, img);
        }

        else
        {
            if(img != NULL)
            {
                // Make sure we have opened a file already
                fwrite(buffer, 1, 512, img);
            }

        }

   }



}