#include<iostream>

#include "v1proc.hpp"

int main(int argc, char** argv) {
    const char *fpath = argv[1];
    int width, height, channels;
    unsigned char *img = nullptr;
    read_png_image(fpath, &img, &width, &height, &channels);
    std::cout << "Image loaded: " << width << "x" << height << " with " << channels << " channels." << std::endl;

    if (channels > 1) {
        unsigned char *gray_img = new unsigned char[width * height];
        rgb_to_grayscale(img, gray_img, width, height, channels);
        delete[] img;
        img = gray_img;
        channels = 1;
    }

    int thresh = threshold(img, width, height, channels);
    std::cout << "Otsu's threshold value: " << thresh << std::endl;

    std::cout << "segmenting image based on the threshold" << std::endl;
    unsigned char *segmented_img = new unsigned char[width * height];
    segment(img, segmented_img, width, height, channels, thresh);
    
    const char *outpath = argv[2];
    if (write_png_image(outpath, segmented_img, width, height, channels) != 0) {
        std::cerr << "failed to write image to: " << outpath << std::endl;
    }
    delete[] segmented_img;

    delete[] img;
    return 0;
}