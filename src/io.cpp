#include "io.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void read_png_image(const char * fpath, unsigned char** img, int * width, int * height, int * channels)
{
    int w, h, c;
    *img = stbi_load(fpath, &w, &h, &c, 0);
    if (*img == NULL) {
        fprintf(stderr, "Error loading image: %s\n", stbi_failure_reason());
        exit(1);
    }
    *width = w;
    *height = h;
    *channels = c;
}

int write_png_image(const char* outpath, unsigned char *img, int width, int height, int channels){
    int success = stbi_write_png(outpath, width, height, channels, img, width * channels);
    if (!success) {
        fprintf(stderr, "Error writing image: %s\n", stbi_failure_reason());
        return -1;
    }
    return 0;
}