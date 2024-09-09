#include "helpers.h"
#include <math.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rgbt = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = rgbt;
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
            RGBTRIPLE temp = image[i][j];  // Swap pixels one at a time
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory dynamically for temp
    RGBTRIPLE (*temp)[width] = malloc(height * sizeof(RGBTRIPLE[width]));
    if (temp == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumBlue = 0, sumGreen = 0, sumRed = 0;
            float counter = 0;

            // Sum surrounding pixels
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    int newRow = i + r;
                    int newCol = j + c;

                    // Ensure we stay within image bounds
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        sumBlue += image[newRow][newCol].rgbtBlue;
                        sumGreen += image[newRow][newCol].rgbtGreen;
                        sumRed += image[newRow][newCol].rgbtRed;
                        counter++;
                    }
                }
            }

            // Compute the average and assign to temp
            temp[i][j].rgbtBlue = round(sumBlue / counter);
            temp[i][j].rgbtGreen = round(sumGreen / counter);
            temp[i][j].rgbtRed = round(sumRed / counter);
        }
    }

    // Copy the blurred values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    // Free the dynamically allocated memory
    free(temp);

    return;
}






// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory dynamically for temp
    RGBTRIPLE (*temp)[width] = malloc(height * sizeof(RGBTRIPLE[width]));
    if (temp == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0, gyBlue = 0;
            int gxGreen = 0, gyGreen = 0;
            int gxRed = 0, gyRed = 0;

            // Loop through the kernel
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    int newRow = i + r;
                    int newCol = j + c;

                    // Ensure we stay within image bounds
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        gxBlue += image[newRow][newCol].rgbtBlue * gx[r + 1][c + 1];
                        gyBlue += image[newRow][newCol].rgbtBlue * gy[r + 1][c + 1];

                        gxGreen += image[newRow][newCol].rgbtGreen * gx[r + 1][c + 1];
                        gyGreen += image[newRow][newCol].rgbtGreen * gy[r + 1][c + 1];

                        gxRed += image[newRow][newCol].rgbtRed * gx[r + 1][c + 1];
                        gyRed += image[newRow][newCol].rgbtRed * gy[r + 1][c + 1];
                    }
                }
            }

            // Compute the gradient magnitude and clamp to 255
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    // Copy the edge-detected values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    // Free the dynamically allocated memory
    free(temp);

    return;
}




// Emboss filter function
void emboss(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory dynamically for temp
    RGBTRIPLE (*temp)[width] = malloc(height * sizeof(RGBTRIPLE[width]));
    if (temp == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    int emboss[3][3] = {{-2, -1, 0},
                        {-1,  1, 1},
                        { 0,  1, 2}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0, green = 0, blue = 0;

            // Loop through the 3x3 convolution kernel
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    int neighbor_row = i + r;
                    int neighbor_col = j + c;

                    // Ensure we stay within image bounds
                    if (neighbor_row >= 0 && neighbor_row < height && neighbor_col >= 0 && neighbor_col < width)
                    {
                        red += image[neighbor_row][neighbor_col].rgbtRed * emboss[r + 1][c + 1];
                        green += image[neighbor_row][neighbor_col].rgbtGreen * emboss[r + 1][c + 1];
                        blue += image[neighbor_row][neighbor_col].rgbtBlue * emboss[r + 1][c + 1];
                    }
                }
            }

            // Clamp the values between 0 and 255
            temp[i][j].rgbtRed = (red > 255) ? 255 : (red < 0) ? 0 : red;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : (green < 0) ? 0 : green;
            temp[i][j].rgbtBlue = (blue > 255) ? 255 : (blue < 0) ? 0 : blue;
        }
    }

    // Copy the embossed values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    // Free the dynamically allocated memory
    free(temp);

    return;
}
