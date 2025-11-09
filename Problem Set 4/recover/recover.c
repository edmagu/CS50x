#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE; // 1 byte (8 bits)

// Block size constant
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Ensure correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file
    FILE *inptr = fopen(argv[1], "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *outptr = NULL;
    char filename[8];
    int file_count = 0;
    int found_jpeg = 0;

    // Read 512 bytes at a time
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // Check for JPEG header
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If already found a JPEG, close the previous one
            if (found_jpeg)
            {
                fclose(outptr);
            }
            else
            {
                found_jpeg = 1; // first JPEG found
            }

            // Create new JPEG filename
            sprintf(filename, "%03i.jpg", file_count);
            outptr = fopen(filename, "wb");
            if (outptr == NULL)
            {
                printf("Could not create %s.\n", filename);
                fclose(inptr);
                return 1;
            }

            file_count++;
        }

        // If a JPEG has been found, write block to it
        if (found_jpeg)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
    }

    // Clean up
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    fclose(inptr);

    return 0;
}
