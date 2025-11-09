// volume.c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Remember filenames and factor
    char *input = argv[1];
    char *output = argv[2];
    float factor = atof(argv[3]);

    // Open input file
    FILE *inputFile = fopen(input, "rb");
    if (inputFile == NULL)
    {
        printf("Could not open %s.\n", input);
        return 1;
    }

    // Open output file
    FILE *outputFile = fopen(output, "wb");
    if (outputFile == NULL)
    {
        printf("Could not create %s.\n", output);
        fclose(inputFile);
        return 1;
    }

    // Copy header
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, inputFile);
    fwrite(header, HEADER_SIZE, 1, outputFile);

    // Read samples and write scaled ones
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, inputFile))
    {
        sample = sample * factor;
        fwrite(&sample, sizeof(int16_t), 1, outputFile);
    }

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
