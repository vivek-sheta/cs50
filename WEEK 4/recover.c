#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s cardname\n", argv[0]);
        return 1;
    }

    char *inname = argv[1];

    FILE *inptr = fopen(inname, "r");

    if (inptr == NULL)
    {
        printf("Not open: %s.\n", inname);
        return 1;
    }

    BYTE buffer[512];
    int imageCount = 0;

    char filename[8];
    FILE *outfile = NULL;

    while (true)
    {
        size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);

        // Check end of file and exit loop
        if (bytesRead == 0 && feof(inptr))
        {
            break;
        }

        // Check JPEG header
        bool isJPEG = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;

        if (isJPEG && (outfile != NULL))
        {
            fclose(outfile);
            imageCount++;
        }

        if (isJPEG)
        {
            sprintf(filename, "%03i.jpg", imageCount);
            outfile = fopen(filename, "w");
        }

        if (outfile != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outfile);
        }
    }
    fclose(outfile);
    fclose(inptr);
    return 0;
}
