#include <iostream>
#include "deskew.h"

int main() {
    // Example: create a small synthetic image and deskew it
    deskewk::Image img;
    img.width = 10;
    img.height = 10;
    img.pixels.assign(img.height, std::vector<int>(img.width, 0));

    // Draw a horizontal line near the middle
    for (int x = 0; x < img.width; ++x) {
        img.pixels[5][x] = 1;
    }

    double angle = deskewk::estimateSkewAngle(img);
    std::cout << "Estimated skew angle: " << angle << " degrees\n";

    deskewk::Image result = deskewk::deskew(img);
    std::cout << "Deskew complete. Output size: "
              << result.width << "x" << result.height << "\n";

    return 0;
}
