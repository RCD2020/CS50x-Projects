#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Failed to open %s.\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER head;
    fread(&head, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(head))
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Failed to open %s.\n", argv[2]);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&head, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(head);
    int blockNum = head.subchunk2Size / blockSize;
    unsigned char blocks[blockNum][blockSize];

    // Write reversed audio to file
    // TODO #8
    for (int i = 0; i < blockNum; i++)
    {
        fread(blocks[i], blockSize, 1, input);
    }

    for (int i = blockNum; i > 0; i--)
    {
        fwrite(blocks[i - 1], blockSize, 1, output);
    }

    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }

    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int size = header.numChannels * header.bitsPerSample / 8;
    return size;
}