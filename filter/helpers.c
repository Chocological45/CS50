#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float r, g, b, avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;

            avg = (r + g + b) / 3.0;

            image[i][j].rgbtRed = roundf(avg);
            image[i][j].rgbtGreen = roundf(avg);
            image[i][j].rgbtBlue = roundf(avg);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE img = image[i][width - j - 1];
            image[i][width - j - 1] = image[i][j];
            image[i][j] = img;

        }
    }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE copy[height][width];


    //Make a copy of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }





    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top Left Corner
            if (i == 0 && j == 0)
            {
                float avgRed = (copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed);
                float avgGreen = (copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen);
                float avgBlue = (copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue);
                image[i][j].rgbtRed = roundf(avgRed / 4.0);
                image[i][j].rgbtGreen = roundf(avgGreen / 4.0);
                image[i][j].rgbtBlue = roundf(avgBlue / 4.0);
            }
            // Bottom Left Corner
            else if (i == height - 1 && j == 0)
            {
                float avgRed = (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed);
                float avgGreen = (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen);
                float avgBlue = (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue);
                image[i][j].rgbtRed = roundf(avgRed / 4.0);
                image[i][j].rgbtGreen = roundf(avgGreen / 4.0);
                image[i][j].rgbtBlue = roundf(avgBlue / 4.0);
            }
            // Top right corner
            else if (i == 0 && j == width - 1)
            {
                float avgRed = (copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed);
                float avgGreen = (copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen);
                float avgBlue = (copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue);
                image[i][j].rgbtRed = roundf(avgRed / 4.0);
                image[i][j].rgbtGreen = roundf(avgGreen / 4.0);
                image[i][j].rgbtBlue = roundf(avgBlue / 4.0);
            }
            // Bottom Right Corner
            else if (i == height - 1 && j == width - 1)
            {
                float avgRed = (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed);
                float avgGreen = (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen);
                float avgBlue = (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue);
                image[i][j].rgbtRed = roundf(avgRed / 4.0);
                image[i][j].rgbtGreen = roundf(avgGreen / 4.0);
                image[i][j].rgbtBlue = roundf(avgBlue / 4.0);
            }
            // Left Side
            else if (j == 0)
            {
                float avgRed = (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed);
                float avgGreen = (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen);
                float avgBlue = (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue);
                image[i][j].rgbtRed = roundf(avgRed / 6.0);
                image[i][j].rgbtGreen = roundf(avgGreen / 6.0);
                image[i][j].rgbtBlue = roundf(avgBlue / 6.0);
            }
            // Right Side
            else if (j == width - 1)
            {
                float avgRed = (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed);
                float avgGreen = (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen);
                float avgBlue = (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue);
                image[i][j].rgbtRed = roundf(avgRed / 6.0);
                image[i][j].rgbtGreen = roundf(avgGreen / 6.0);
                image[i][j].rgbtBlue = roundf(avgBlue / 6.0);
            }
            // Top Side
            else if (i == 0)
            {
                float avgRed = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed);
                float avgGreen = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen);
                float avgBlue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue);
                image[i][j].rgbtRed = roundf(avgRed / 6.0);
                image[i][j].rgbtGreen = roundf(avgGreen / 6.0);
                image[i][j].rgbtBlue = roundf(avgBlue / 6.0);
            }
            // Bottom Side
            else if (i == height - 1)
            {
                float avgRed = (copy[i][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed);
                float avgGreen = (copy[i][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen);
                float avgBlue = (copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue);
                image[i][j].rgbtRed = roundf(avgRed / 6.0);
                image[i][j].rgbtGreen = roundf(avgGreen / 6.0);
                image[i][j].rgbtBlue = roundf(avgBlue / 6.0);
            }
            // Middle
            else if ((i != 0 && i != height - 1) && (j != 0 && j != width - 1))
            {
                float avgRed = (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed);
                float avgGreen = (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen);
                float avgBlue = (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue);
                image[i][j].rgbtRed = roundf(avgRed / 9.0);
                image[i][j].rgbtGreen = roundf(avgGreen / 9.0);
                image[i][j].rgbtBlue = roundf(avgBlue / 9.0);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //  gx and gy values              Final RGB values
    int gxR, gxG, gxB, gyR, gyB, gyG, finalR, finalG, finalB;

    //Declare a copy image
    RGBTRIPLE copy[height][width];

    //Make copy of src image
    memcpy(copy, image, sizeof(RGBTRIPLE) * height * width);

    //Loop through all pixels in the copy image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top Left Corner
            if (i == 0 && j == 0)
            {
                //GX calculations
                gxR = (copy[i][j + 1].rgbtRed * 2)  + (copy[i + 1][j + 1].rgbtRed * 1);
                gxG = (copy[i][j + 1].rgbtGreen * 2)  + (copy[i + 1][j + 1].rgbtGreen * 1);
                gxB = (copy[i][j + 1].rgbtBlue * 2)  + (copy[i + 1][j + 1].rgbtBlue * 1);

                //GY calculations
                gyR = (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed * 1);
                gyG = (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen * 1);
                gyB = (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue * 1);

                //Final RGB calculations
                finalR = round(sqrt((pow(gxR, 2) + pow(gyR, 2))));
                finalG = round(sqrt((pow(gxG, 2) + pow(gyG, 2))));
                finalB = round(sqrt((pow(gxB, 2) + pow(gyB, 2))));

                //Make sure pixel does not exceed 255
                if (finalR > 255)
                {
                    finalR = 255;
                }
                if (finalG > 255)
                {
                    finalG = 255;
                }
                if (finalB > 255)
                {
                    finalB = 255;
                }

                //Update original image
                image[i][j].rgbtRed = finalR;
                image[i][j].rgbtGreen = finalG;
                image[i][j].rgbtBlue = finalB;
            }
            // Bottom Left Corner
            else if (i == height - 1 && j == 0)
            {
                //GX calculations
                gxR = (copy[i][j + 1].rgbtRed * 2)  + (copy[i - 1][j + 1].rgbtRed * 1);
                gxG = (copy[i][j + 1].rgbtGreen * 2)  + (copy[i - 1][j + 1].rgbtGreen * 1);
                gxB = (copy[i][j + 1].rgbtBlue * 2)  + (copy[i - 1][j + 1].rgbtBlue * 1);

                //GY calculations
                gyR = (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j + 1].rgbtRed * -1);
                gyG = (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j + 1].rgbtGreen * -1);
                gyB = (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j + 1].rgbtBlue * -1);

                //Final RGB calculations
                finalR = round(sqrt((pow(gxR, 2) + pow(gyR, 2))));
                finalG = round(sqrt((pow(gxG, 2) + pow(gyG, 2))));
                finalB = round(sqrt((pow(gxB, 2) + pow(gyB, 2))));

                //Make sure pixel does not exceed 255
                if (finalR > 255)
                {
                    finalR = 255;
                }
                if (finalG > 255)
                {
                    finalG = 255;
                }
                if (finalB > 255)
                {
                    finalB = 255;
                }

                //Update original image
                image[i][j].rgbtRed = finalR;
                image[i][j].rgbtGreen = finalG;
                image[i][j].rgbtBlue = finalB;
            }
            // Top right corner
            else if (i == 0 && j == width - 1)
            {
                //GX calculations
                gxR = (copy[i][j - 1].rgbtRed * -2)  + (copy[i + 1][j - 1].rgbtRed * -1);
                gxG = (copy[i][j - 1].rgbtGreen * -2)  + (copy[i + 1][j - 1].rgbtGreen * -1);
                gxB = (copy[i][j - 1].rgbtBlue * -2)  + (copy[i + 1][j - 1].rgbtBlue * -1);

                //GY calculations
                gyR = (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j - 1].rgbtRed * 1);
                gyG = (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j - 1].rgbtGreen * 1);
                gyB = (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j - 1].rgbtBlue * 1);

                //Final RGB calculations
                finalR = round(sqrt((pow(gxR, 2) + pow(gyR, 2))));
                finalG = round(sqrt((pow(gxG, 2) + pow(gyG, 2))));
                finalB = round(sqrt((pow(gxB, 2) + pow(gyB, 2))));

                //Make sure pixel does not exceed 255
                if (finalR > 255)
                {
                    finalR = 255;
                }
                if (finalG > 255)
                {
                    finalG = 255;
                }
                if (finalB > 255)
                {
                    finalB = 255;
                }

                //Update original image
                image[i][j].rgbtRed = finalR;
                image[i][j].rgbtGreen = finalG;
                image[i][j].rgbtBlue = finalB;
            }
            // Bottom Right Corner
            else if (i == height - 1 && j == width - 1)
            {
                //GX calculations
                gxR = (copy[i][j - 1].rgbtRed * -2)  + (copy[i - 1][j - 1].rgbtRed * -1);
                gxG = (copy[i][j - 1].rgbtGreen * -2)  + (copy[i - 1][j - 1].rgbtGreen * -1);
                gxB = (copy[i][j - 1].rgbtBlue * -2)  + (copy[i - 1][j - 1].rgbtBlue * -1);

                //GY calculations
                gyR = (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j - 1].rgbtRed * -1);
                gyG = (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j - 1].rgbtGreen * -1);
                gyB = (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j - 1].rgbtBlue * -1);

                //Final RGB calculations
                finalR = round(sqrt((pow(gxR, 2) + pow(gyR, 2))));
                finalG = round(sqrt((pow(gxG, 2) + pow(gyG, 2))));
                finalB = round(sqrt((pow(gxB, 2) + pow(gyB, 2))));

                //Make sure pixel does not exceed 255
                if (finalR > 255)
                {
                    finalR = 255;
                }
                if (finalG > 255)
                {
                    finalG = 255;
                }
                if (finalB > 255)
                {
                    finalB = 255;
                }

                //Update original image
                image[i][j].rgbtRed = finalR;
                image[i][j].rgbtGreen = finalG;
                image[i][j].rgbtBlue = finalB;
            }
            // Left Side
            else if (j == 0)
            {
                //GX calculations
                gxR = (copy[i - 1][j + 1].rgbtRed) + (copy[i][j + 1].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed);
                gxG = (copy[i - 1][j + 1].rgbtGreen) + (copy[i][j + 1].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen);
                gxB = (copy[i - 1][j + 1].rgbtBlue) + (copy[i][j + 1].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue);

                //GY calculations
                gyR = (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j + 1].rgbtRed * -1) + (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed);
                gyG = (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j + 1].rgbtGreen * -1) + (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen);
                gyB = (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j + 1].rgbtBlue * -1) + (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue);

                //Final RGB calculations
                finalR = round(sqrt((pow(gxR, 2) + pow(gyR, 2))));
                finalG = round(sqrt((pow(gxG, 2) + pow(gyG, 2))));
                finalB = round(sqrt((pow(gxB, 2) + pow(gyB, 2))));

                //Make sure pixel does not exceed 255
                if (finalR > 255)
                {
                    finalR = 255;
                }
                if (finalG > 255)
                {
                    finalG = 255;
                }
                if (finalB > 255)
                {
                    finalB = 255;
                }

                //Update original image
                image[i][j].rgbtRed = finalR;
                image[i][j].rgbtGreen = finalG;
                image[i][j].rgbtBlue = finalB;
            }
            // Right Side
            else if (j == width - 1)
            {
                //GX calculations
                gxR = (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i][j - 1].rgbtRed * -2) + (copy[i + 1][j - 1].rgbtRed * -1);
                gxG = (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i][j - 1].rgbtGreen * -2) + (copy[i + 1][j - 1].rgbtGreen * -1);
                gxB = (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i][j - 1].rgbtBlue * -2) + (copy[i + 1][j - 1].rgbtBlue * -1);

                //GY calculations
                gyR = (copy[i - 1][j].rgbtRed * -2) + (copy[i + 1][j].rgbtRed * 2) + (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i + 1][j - 1].rgbtRed);
                gyG = (copy[i - 1][j].rgbtGreen * -2) + (copy[i + 1][j].rgbtGreen * 2) + (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i + 1][j - 1].rgbtGreen);
                gyB = (copy[i - 1][j].rgbtBlue * -2) + (copy[i + 1][j].rgbtBlue * 2) + (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i + 1][j - 1].rgbtBlue);

                //Final RGB calculations
                finalR = round(sqrt((pow(gxR, 2) + pow(gyR, 2))));
                finalG = round(sqrt((pow(gxG, 2) + pow(gyG, 2))));
                finalB = round(sqrt((pow(gxB, 2) + pow(gyB, 2))));

                //Make sure pixel does not exceed 255
                if (finalR > 255)
                {
                    finalR = 255;
                }
                if (finalG > 255)
                {
                    finalG = 255;
                }
                if (finalB > 255)
                {
                    finalB = 255;
                }

                //Update original image
                image[i][j].rgbtRed = finalR;
                image[i][j].rgbtGreen = finalG;
                image[i][j].rgbtBlue = finalB;
            }
            // Top Side
            else if (i == 0)
            {
                //GX calculations
                gxR = (copy[i][j - 1].rgbtRed * -2) + (copy[i][j + 1].rgbtRed * 2) + (copy[i + 1][j - 1].rgbtRed * -1) + (copy[i + 1][j + 1].rgbtRed);
                gxG = (copy[i][j - 1].rgbtGreen * -2) + (copy[i][j + 1].rgbtGreen * 2) + (copy[i + 1][j - 1].rgbtGreen * -1) + (copy[i + 1][j + 1].rgbtGreen);
                gxB = (copy[i][j - 1].rgbtBlue * -2) + (copy[i][j + 1].rgbtBlue * 2) + (copy[i + 1][j - 1].rgbtBlue * -1) + (copy[i + 1][j + 1].rgbtBlue);

                //GY calculations
                gyR = (copy[i + 1][j - 1].rgbtRed) + (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed);
                gyG = (copy[i + 1][j - 1].rgbtGreen) + (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen);
                gyB = (copy[i + 1][j - 1].rgbtBlue) + (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue);

                //Final RGB calculations
                finalR = round(sqrt((pow(gxR, 2) + pow(gyR, 2))));
                finalG = round(sqrt((pow(gxG, 2) + pow(gyG, 2))));
                finalB = round(sqrt((pow(gxB, 2) + pow(gyB, 2))));

                //Make sure pixel does not exceed 255
                if (finalR > 255)
                {
                    finalR = 255;
                }
                if (finalG > 255)
                {
                    finalG = 255;
                }
                if (finalB > 255)
                {
                    finalB = 255;
                }

                //Update original image
                image[i][j].rgbtRed = finalR;
                image[i][j].rgbtGreen = finalG;
                image[i][j].rgbtBlue = finalB;
            }
            // Bottom Side
            else if (i == height - 1)
            {
                //GX calculations
                gxR = (copy[i][j - 1].rgbtRed * -2) + (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i - 1][j].rgbtRed * 0) + (copy[i - 1][j + 1].rgbtRed * 1) + (copy[i][j + 1].rgbtRed * 2);
                gxG = (copy[i][j - 1].rgbtGreen * -2) + (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i - 1][j].rgbtGreen * 0) + (copy[i - 1][j + 1].rgbtGreen * 1) + (copy[i][j + 1].rgbtGreen * 2);
                gxB = (copy[i][j - 1].rgbtBlue * -2) + (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i - 1][j].rgbtBlue * 0) + (copy[i - 1][j + 1].rgbtBlue * 1) + (copy[i][j + 1].rgbtBlue * 2);

                //GY calculations
                gyR = (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j + 1].rgbtRed * -1);
                gyG = (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j + 1].rgbtGreen * -1);
                gyB = (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j + 1].rgbtBlue * -1);

                //Final RGB calculations
                finalR= round(sqrt((pow(gxR, 2) + pow(gyR, 2))));
                finalG = round(sqrt((pow(gxG, 2) + pow(gyG, 2))));
                finalB = round(sqrt((pow(gxB, 2) + pow(gyB, 2))));

                //Make sure pixel does not exceed 255
                if (finalR > 255)
                {
                    finalR = 255;
                }
                if (finalG > 255)
                {
                    finalG = 255;
                }
                if (finalB > 255)
                {
                    finalB = 255;
                }

                //Update original image
                image[i][j].rgbtRed = finalR;
                image[i][j].rgbtGreen = finalG;
                image[i][j].rgbtBlue = finalB;
            }
            // Middle
            else if ((i != 0 && i != height - 1) && (j != 0 && j != width - 1))
            {
                //GX calculations
                gxR = (copy[i][j - 1].rgbtRed * -2) + (copy[i][j + 1].rgbtRed * 2) + (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i - 1][j + 1].rgbtRed) + (copy[i + 1][j - 1].rgbtRed * -1) + (copy[i + 1][j + 1].rgbtRed);
                gxG = (copy[i][j - 1].rgbtGreen * -2) + (copy[i][j + 1].rgbtGreen * 2) + (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i - 1][j + 1].rgbtGreen) + (copy[i + 1][j - 1].rgbtGreen * -1) + (copy[i + 1][j + 1].rgbtGreen);
                gxB = (copy[i][j - 1].rgbtBlue * -2) + (copy[i][j + 1].rgbtBlue * 2) + (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i - 1][j + 1].rgbtBlue) + (copy[i + 1][j - 1].rgbtBlue * -1) + (copy[i + 1][j + 1].rgbtBlue);

                //GY calculations
                gyR = (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i - 1][j + 1].rgbtRed * -1) + (copy[i + 1][j - 1].rgbtRed) + (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed);
                gyB = (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i - 1][j + 1].rgbtBlue * -1) + (copy[i + 1][j - 1].rgbtBlue) + (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue);
                gyG = (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i - 1][j + 1].rgbtGreen * -1) + (copy[i + 1][j - 1].rgbtGreen) + (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen);

                //Final RGB calculations
                finalR = round(sqrt((pow(gxR, 2) + pow(gyR, 2))));
                finalG = round(sqrt((pow(gxG, 2) + pow(gyG, 2))));
                finalB = round(sqrt((pow(gxB, 2) + pow(gyB, 2))));

                //Make sure pixel does not exceed 255
                if (finalR > 255)
                {
                    finalR = 255;
                }
                if (finalG > 255)
                {
                    finalG = 255;
                }
                if (finalB > 255)
                {
                    finalB = 255;
                }

                //Update original image
                image[i][j].rgbtRed = finalR;
                image[i][j].rgbtGreen = finalG;
                image[i][j].rgbtBlue = finalB;
            }
        }
    }
    return;
}