#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE R, G, B;
    float avg = 0.0;
    int val = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            R = image[i][j].rgbtRed;
            G = image[i][j].rgbtGreen;
            B = image[i][j].rgbtBlue;

            avg = (float)(R + G + B) / 3.0;
            val = round(avg);

            image[i][j].rgbtRed = val;
            image[i][j].rgbtGreen = val;
            image[i][j].rgbtBlue = val;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE R, G, B;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            R = image[i][j].rgbtRed;
            G = image[i][j].rgbtGreen;
            B = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = R;
            image[i][width - j - 1].rgbtGreen = G;
            image[i][width - j - 1].rgbtBlue = B;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int R, G, B;
    float counter;
    // Create temp variable contain copy of image for pocessing
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // Set value after each round completed
            R = G = B = 0;
            counter = 0.00;

            for (int k = -1; k < 2; k++)
            {
                // Check for boundry (height)
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    // Check boundary (width)
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    // Add the value of individual pixel
                    B += image[j + k][i + h].rgbtBlue;
                    G += image[j + k][i + h].rgbtGreen;
                    R += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            // Set roundof to temp variable
            temp[j][i].rgbtRed = round(R / counter);
            temp[j][i].rgbtGreen = round(G / counter);
            temp[j][i].rgbtBlue = round(B / counter);
        }
    }

    // Set data temp variable to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
}

//edges Detect
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int RX, GX, BX, RY, GY, BY;

    // Create temp variable contain copy of image for pocessing
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RX = GX = BX = RY = GY = BY = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    // check pixels in or out edge
                    if (i - 1 + k < 0 || i - 1 + k > height - 1 || j - 1 + l < 0 || j - 1 + l > width - 1)
                    {
                        continue;
                    }

                    // calcuate Gx for individual color
                    RX += image[i - 1 + k][j - 1 + l].rgbtRed * Gx[k][l];
                    GX += image[i - 1 + k][j - 1 + l].rgbtGreen * Gx[k][l];
                    BX += image[i - 1 + k][j - 1 + l].rgbtBlue * Gx[k][l];

                    // calculate Gy for individual color
                    RY += image[i - 1 + k][j - 1 + l].rgbtRed * Gy[k][l];
                    GY += image[i - 1 + k][j - 1 + l].rgbtGreen * Gy[k][l];
                    BY += image[i - 1 + k][j - 1 + l].rgbtBlue * Gy[k][l];
                }
            }

            float r = sqrt((RX * RX) + (RY * RY));
            float g = sqrt((GX * GX) + (GY * GY));
            float b = sqrt((BX * BX) + (BY * BY));

            // Chcek value out of range if yes then set max value 255
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }

            if (b > 255)
            {
                b = 255;
            }

            int red =  round(r);
            int green = round(g);
            int blue = round(b);
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
        }
    }

    // Set data temp variable to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
