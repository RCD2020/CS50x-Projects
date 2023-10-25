#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    unsigned char data[512] = {};
    char name[] = "000.jpg";
    int counter = 0;
    int isWrite = 0;
    FILE *output;

    while (fread(data, sizeof(data), 1, input))
    {
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && (data[3] >> 4) == 0x0e)
        {
            name[0] = '0' + counter % 1000 / 100;
            name[1] = '0' + counter % 100 / 10;
            name[2] = '0' + counter % 10;

            counter++;

            if (isWrite)
            {
                fclose(output);
            }
            else
            {
                isWrite = 1;
            }

            output = fopen(name, "w");
            if (output == NULL)
            {
                fclose(input);
                fclose(output);
                printf("Could not allocate memory\n");
                return 2;
            }
        }

        if (isWrite)
        {
            // for (int i = 0; i < 512; i++)
            // {
            //     fwrite(&data[i], sizeof(unsigned char), 1, output);
            // }

            fwrite(data, sizeof(data), 1, output);
        }
    }

    fclose(input);
    fclose(output);
}