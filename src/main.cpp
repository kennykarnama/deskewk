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

    std::vector<int> projection = horizontal_projection(segmented_img, width, height, channels);
    const char *projection_outpath = argv[3];
    if (write_horizontal_projection_image(projection, width, projection_outpath) != 0) {
        std::cerr << "failed to write horizontal projection image to: " << projection_outpath << std::endl;
    }

    std::vector<int> verticalProjection = vertical_projection(segmented_img, width, height, channels);
    const char *vertical_projection_outpath = argv[4];
    if (write_vertical_projection_image(verticalProjection, height, vertical_projection_outpath) != 0) {
        std::cerr << "failed to write vertical projection image to: " << vertical_projection_outpath << std::endl;
    }

    delete[] segmented_img;
    delete[] img;
    return 0;
}