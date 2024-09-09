#include "bmp.h"

// convert to grayscale (black and white)
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// detect edges, matrix-feel
void edges(int height, int width, RGBTRIPLE image[height][width]);

// blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

void emboss(int height, int width, RGBTRIPLE image[height][width]);

