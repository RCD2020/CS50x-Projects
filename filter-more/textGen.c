#include <stdio.h>

int main(void)
{
    char gx[] = "-2 * ";
    char gy[] = "0 * ";
    int xOffset = 1;
    int yOffset = 0;
    char xdir = '-';
    char ydir = '+';

    char xOffsetText[5] = {'\0'};
    char yOffsetText[5] = {'\0'};

    if (xOffset) {
        xOffsetText[0] = ' ';
        xOffsetText[1] = xdir;
        xOffsetText[2] = ' ';
        xOffsetText[3] = '1';
        xOffsetText[4] = '\0';
    }
    if (yOffset) {
        yOffsetText[0] = ' ';
        yOffsetText[1] = ydir;
        yOffsetText[2] = ' ';
        yOffsetText[3] = '1';
        yOffsetText[4] = '\0';
    }

    printf("rgx += %simage[x%s][y%s].rgbtRed;\n", gx, xOffsetText, yOffsetText);
    printf("ggx += %simage[x%s][y%s].rgbtGreen;\n", gx, xOffsetText, yOffsetText);
    printf("bgx += %simage[x%s][y%s].rgbtBlue;\n", gx, xOffsetText, yOffsetText);
    printf("rgy += %simage[x%s][y%s].rgbtRed;\n", gy, xOffsetText, yOffsetText);
    printf("ggy += %simage[x%s][y%s].rgbtGreen;\n", gy, xOffsetText, yOffsetText);
    printf("bgy += %simage[x%s][y%s].rgbtBlue;\n", gy, xOffsetText, yOffsetText);
}