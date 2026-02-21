#include<iostream>

#include "v1proc.hpp"
#include "deskew.hpp"

int main(int argc, char** argv) {
    const char *fpath = argv[1];
    int width, height, channels;
    unsigned char *img = nullptr;
    read_png_image(fpath, &img, &width, &height, &channels);
    std::cout << "Image loaded: " << width << "x" << height << " with " << channels << " channels." << std::endl;

    IntermediaryImageOutput intermediaryOpt;
    intermediaryOpt.output_dir = "./processed_images";
    intermediaryOpt.write_rotations = true;
    intermediaryOpt.write_projections = true;
    intermediaryOpt.write_bb = true;
    intermediaryOpt.write_segmented = true;

    double theta = estimated_skew_angle(img, width, height, channels, &intermediaryOpt);
    std::cout << "Estimated skew angle: " << theta << " degrees." << std::endl;

    unsigned char *deskewed_img = new unsigned char[width * height * channels];

    simple_rotate(img, deskewed_img, width, height, channels, theta);

    write_png_image("./deskewed.png", deskewed_img, width, height, channels);

    return 0;
}