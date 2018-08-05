#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

#include "rcv.h"

int main (int argc, char *argv[]){

    if (argc != 2)

    {
        fprintf(stderr, "User: Check number of arguments");
    }

    return 1;

    char *inphotofile = argv[1];

    FILE *delpic = fopen(inphotofile, "r");

    if(inphotofile == NULL)

    {
        fprintf(stderr, "User: file could not open");
        return 2;
    }


    DELETEDBYTE bi;


    for (int i = 0; i = bSize; i++) {

        fread(&bSize, 1, DELETEDBYTESIZE, delPic);
}
    // One blocks at 512 byte
    //fread(inpic, 512, 1, raw_file); // 512 blocks at 1 byte

/*
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 )
    {
        // If all this passes to be true, you hit the beginning of a new JPEG


        // Mking a new file to store each time

        sprintf(//filename, "%03i.jpg", 2) // craetes filename for new jpeg

        // ###.jpg // Name in which the order they were found starting at 000

        FILE *img = fopen(//filename, "w");

        fwrite(&inpic, sizeof(), 1, outptr); // needs to write 512 bytes at a time
    }
*/


}