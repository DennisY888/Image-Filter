# Spelling Verifier
### Skills
- C, pixel manipulation, file I/O, BMP file format, RGB color model
### Supported Filters
- Emboss 
  - gives image a 3D-like effect by emphasizing the differences between neighboring pixels 
  - Using convolution matrix, for each pixel , we multiply the color values (red, green, and blue) of each pixel surrounding it by the corresponding number in the emboss matrix 
  - The RGB values of all surrounding pixels are summed up and applied to current pixel 
- Edge Detection 
  - Sobel operator was used for edge detection 
- Grayscale 
  - Take the average of RGB values and set all three RGB as the average for each pixel 
- Reflection 
  - Switch the locations of the left-most pixels and corresponding right-most pixels all the way until reaching center 
- Blur 
  - Box blur: averaging the color values of neighboring pixels and assign it to each pixel 
### How this program works
- Load the BMP file: The program reads the image and stores its pixel data in a 2D array. 
- Apply the filter: Based on the command-line argument (grayscale, reflection, blur, or edges), the corresponding function is called to modify the pixel data. 
- Write the new image: After applying the filter, the modified pixel data is written to a new BMP file. 
### Usage in terminal
- “make filter” 
- Grayscale 
  - ./filter -g [input.bmp] [output.bmp] 
- Reflection 
  - /filter -r [input.bmp] [output.bmp] 
- Blur 
  - /filter -g [input.bmp] [output.bmp] 
- Edge Detection 
  - /filter -e [input.bmp] [output.bmp] 
- Emboss 
  - /filter -m [input.bmp] [output.bmp] 

