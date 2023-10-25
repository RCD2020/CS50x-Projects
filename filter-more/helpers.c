#include "helpers.h"
#include <math.h>

typedef struct
{
    int r;
    int g;
    int b;
} returnableRGB;

returnableRGB calculateG(int x, int y, int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            avg = (image[h][w].rgbtRed + image[h][w].rgbtBlue + image[h][w].rgbtGreen) / 3.0 + 0.5;
            image[h][w].rgbtRed = avg;
            image[h][w].rgbtBlue = avg;
            image[h][w].rgbtGreen = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE taxi;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            taxi = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = taxi;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float counter;
    int ravg;
    int gavg;
    int bavg;
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            counter = 1;
            ravg = image[h][w].rgbtRed;
            gavg = image[h][w].rgbtGreen;
            bavg = image[h][w].rgbtBlue;

            if (h != 0 && w != 0)
            {
                ravg += image[h - 1][w - 1].rgbtRed;
                gavg += image[h - 1][w - 1].rgbtGreen;
                bavg += image[h - 1][w - 1].rgbtBlue;
                counter++;
            }
            if (h != 0)
            {
                ravg += image[h - 1][w].rgbtRed;
                gavg += image[h - 1][w].rgbtGreen;
                bavg += image[h - 1][w].rgbtBlue;
                counter++;
            }
            if (h != 0 && w != width - 1)
            {
                ravg += image[h - 1][w + 1].rgbtRed;
                gavg += image[h - 1][w + 1].rgbtGreen;
                bavg += image[h - 1][w + 1].rgbtBlue;
                counter++;
            }
            if (w != width - 1)
            {
                ravg += image[h][w + 1].rgbtRed;
                gavg += image[h][w + 1].rgbtGreen;
                bavg += image[h][w + 1].rgbtBlue;
                counter++;
            }
            if (h != height - 1 && w != width - 1)
            {
                ravg += image[h + 1][w + 1].rgbtRed;
                gavg += image[h + 1][w + 1].rgbtGreen;
                bavg += image[h + 1][w + 1].rgbtBlue;
                counter++;
            }
            if (h != height - 1)
            {
                ravg += image[h + 1][w].rgbtRed;
                gavg += image[h + 1][w].rgbtGreen;
                bavg += image[h + 1][w].rgbtBlue;
                counter++;
            }
            if (h != height - 1 && w != 0)
            {
                ravg += image[h + 1][w - 1].rgbtRed;
                gavg += image[h + 1][w - 1].rgbtGreen;
                bavg += image[h + 1][w - 1].rgbtBlue;
                counter++;
            }
            if (w != 0)
            {
                ravg += image[h][w - 1].rgbtRed;
                gavg += image[h][w - 1].rgbtGreen;
                bavg += image[h][w - 1].rgbtBlue;
                counter++;
            }

            ravg = ravg / counter + 0.5;
            gavg = gavg / counter + 0.5;
            bavg = bavg / counter + 0.5;
            copy[h][w].rgbtRed = ravg;
            copy[h][w].rgbtGreen = gavg;
            copy[h][w].rgbtBlue = bavg;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = copy[h][w];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    returnableRGB rgb[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            rgb[h][w] = calculateG(h, w, height, width, image);
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = rgb[h][w].r;
            image[h][w].rgbtGreen = rgb[h][w].g;
            image[h][w].rgbtBlue = rgb[h][w].b;
        }
    }

    return;
}

returnableRGB calculateG(int h, int w, int height, int width, RGBTRIPLE image[height][width])
{
    int rgx = 0;
    int rgy = 0;
    int ggx = 0;
    int ggy = 0;
    int bgx = 0;
    int bgy = 0;

    if (h != 0 && w != 0)
    {
        rgx += -1 * image[h - 1][w - 1].rgbtRed;
        rgy += -1 * image[h - 1][w - 1].rgbtRed;
        ggx += -1 * image[h - 1][w - 1].rgbtGreen;
        ggy += -1 * image[h - 1][w - 1].rgbtGreen;
        bgx += -1 * image[h - 1][w - 1].rgbtBlue;
        bgy += -1 * image[h - 1][w - 1].rgbtBlue;
    }
    if (h != 0)
    {
        rgy += -2 * image[h - 1][w].rgbtRed;
        ggy += -2 * image[h - 1][w].rgbtGreen;
        bgy += -2 * image[h - 1][w].rgbtBlue;
    }
    if (h != 0 && w != width - 1)
    {
        rgx += image[h - 1][w + 1].rgbtRed;
        ggx += image[h - 1][w + 1].rgbtGreen;
        bgx += image[h - 1][w + 1].rgbtBlue;
        rgy += -1 * image[h - 1][w + 1].rgbtRed;
        ggy += -1 * image[h - 1][w + 1].rgbtGreen;
        bgy += -1 * image[h - 1][w + 1].rgbtBlue;
    }
    if (w != width - 1)
    {
        rgx += 2 * image[h][w + 1].rgbtRed;
        ggx += 2 * image[h][w + 1].rgbtGreen;
        bgx += 2 * image[h][w + 1].rgbtBlue;
    }
    if (h != height - 1 && w != width - 1)
    {
        rgx += image[h + 1][w + 1].rgbtRed;
        ggx += image[h + 1][w + 1].rgbtGreen;
        bgx += image[h + 1][w + 1].rgbtBlue;
        rgy += image[h + 1][w + 1].rgbtRed;
        ggy += image[h + 1][w + 1].rgbtGreen;
        bgy += image[h + 1][w + 1].rgbtBlue;
    }
    if (h != height - 1)
    {
        rgy += 2 * image[h + 1][w].rgbtRed;
        ggy += 2 * image[h + 1][w].rgbtGreen;
        bgy += 2 * image[h + 1][w].rgbtBlue;
    }
    if (h != height - 1 && w != 0)
    {
        rgx += -1 * image[h + 1][w - 1].rgbtRed;
        ggx += -1 * image[h + 1][w - 1].rgbtGreen;
        bgx += -1 * image[h + 1][w - 1].rgbtBlue;
        rgy += image[h + 1][w - 1].rgbtRed;
        ggy += image[h + 1][w - 1].rgbtGreen;
        bgy += image[h + 1][w - 1].rgbtBlue;
    }
    if (w != 0)
    {
        rgx += -2 * image[h][w - 1].rgbtRed;
        ggx += -2 * image[h][w - 1].rgbtGreen;
        bgx += -2 * image[h][w - 1].rgbtBlue;
    }

    int rg = rgx * rgx + rgy * rgy;
    int gg = ggx * ggx + ggy * ggy;
    int bg = bgx * bgx + bgy * bgy;
    rg = (int) (sqrt((double) rg) + 0.5);
    gg = (int) (sqrt((double) gg) + 0.5);
    bg = (int) (sqrt((double) bg) + 0.5);

    returnableRGB rgb;
    rgb.r = (rg > 255) ? 255 : rg;
    rgb.g = (gg > 255) ? 255 : gg;
    rgb.b = (bg > 255) ? 255 : bg;

    return rgb;
}