#pragma once

#include <vector>

namespace deskewk {

struct Image {
    std::vector<std::vector<int>> pixels;
    int width;
    int height;
};

// Estimate the skew angle (in degrees) of the given image using
// horizontal projection profiles.
double estimateSkewAngle(const Image& image);

// Automatically estimate and correct the skew angle of the given image.
Image deskew(const Image& image);

} // namespace deskewk
