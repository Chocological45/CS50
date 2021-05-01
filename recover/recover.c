#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }



    //Open memory card
    FILE *src = fopen(argv[1], "r");
    int fCounter = 0;

    //Pointer for filename memory allocation and jpeg img
    char *filename = malloc(50 * sizeof(unsigned int));
    FILE *img = NULL;

    //Initialize a 512 byte buffer
    unsigned char buffer[512];


    //Read 512 bytes into a buffer
    while (fread(&buffer, 512, 1, src) == 1)
    {

        //Check first 4 bytes
        //If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            //If first JPEG
            if (fCounter == 0)
            {

                //Begin writing very first file ie. "000.jpg"

                //Set name of memeory allocation
                sprintf(filename, "%03i.jpg", fCounter);
                //Open file with name
                img = fopen(filename, "w");
                //Write buffer to file
                fwrite(buffer, 512, 1, img);
                fCounter++;
            }
            else if (fCounter != 0)
            {
                //If JPEG already found
                fclose(img);

                //Write to new file
                sprintf(filename, "%03i.jpg", fCounter);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                fCounter++;
            }
        }
        else
        {
            if (fCounter != 0)
            {
                //If already found JPEG
                //Keep writing to file

                fwrite(buffer, 512, 1, img);
            }
        }
    }

    fclose(src);
    return 0;
}
