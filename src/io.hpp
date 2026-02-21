#ifndef IO_HPP
#define IO_HPP

void read_png_image(const char* fpath, unsigned char **img, int *width, int *height, int* channels);

int write_png_image(const char* outpath, unsigned char *img, int width, int height, int channels);

#endif