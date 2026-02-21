#ifndef IO_HPP
#define IO_HPP

// read_png_image reads a PNG image from the given file path and stores the pixel data in the provided img buffer.
void read_png_image(const char* fpath, unsigned char **img, int *width, int *height, int* channels);

int write_png_image(const char* outpath, unsigned char *img, int width, int height, int channels);

#endif