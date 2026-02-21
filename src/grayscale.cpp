#include "grayscale.hpp"

void rgb_to_grayscale(const unsigned char * src, unsigned char * dst, int width, int height, int channels)
{
    int dim = width * height;

    for (int i = 0; i < dim; i++) {
        int r = src[i * channels + 0];
        int g = src[i * channels + 1];
        int b = src[i * channels + 2];

        dst[i] = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
    }
}