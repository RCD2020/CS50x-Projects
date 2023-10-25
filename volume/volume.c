// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef struct
{
    // "RIFF" header
    unsigned char chunkID[4]; // contains "RIFF" in ASCII (why??)
    unsigned int chunkSize;   // size of file after this point
    unsigned char format[4];  // contains "WAVE" in ASCII (why??)

    // "fmt " subchunk describes the sound data's format
    unsigned char subchunk1ID[4]; // contains "fmt\0"
    unsigned int subchunk1Size;   // contains the length of remaining subchunk 1 data. (16)
    unsigned short audioFormat;   // 1 = Pulse Code Modulation (PCM) any other value indicates that there is compression(?)
    unsigned short numChannels;   // mono audio = 1; stereo = 2
    unsigned int sampleRate;      // sample rate: number of samples per second
    unsigned int byterate;        // bytes per second == sampleRate * numChannels * bitsPerSample / 8
    unsigned short blockAlign;    // number of bytes per second including all channels == numChannels * bitPerSample / 8
    unsigned short bitsPerSample; // bits per sample
    // could be more to "fmt " if != PCM

    // "data" subchunk, contains the actual file data
    unsigned char subchunk2ID[4]; // "data"
    unsigned int subchunk2Size;   // number of samples * numChannels * bitsPerSample / 8
    // everything after this is the sample data
} wavHeader;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    wavHeader head;
    fread(&head, sizeof(wavHeader), 1, input);
    fwrite(&head, sizeof(wavHeader), 1, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
