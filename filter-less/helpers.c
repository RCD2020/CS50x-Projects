#include "helpers.h"

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // math:
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

    // sepias
    int sr;
    int sg;
    int sb;
    // originals
    int ogr;
    int og;
    int ob;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            ogr = image[h][w].rgbtRed;
            og = image[h][w].rgbtGreen;
            ob = image[h][w].rgbtBlue;

            sr = .393 * ogr + .769 * og + .189 * ob + 0.5;
            sg = .349 * ogr + .686 * og + .168 * ob + 0.5;
            sb = .272 * ogr + .534 * og + .131 * ob + 0.5;
            if (sr > 0xff)
            {
                sr = 0xff;
            }
            if (sg > 0xff)
            {
                sg = 0xff;
            }
            if (sb > 0xff)
            {
                sb = 0xff;
            }

            image[h][w].rgbtRed = sr;
            image[h][w].rgbtGreen = sg;
            image[h][w].rgbtBlue = sb;
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