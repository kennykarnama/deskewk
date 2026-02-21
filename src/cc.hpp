#ifndef CC_HPP
#define CC_HPP

#include<vector>

// mbr computes the minimum bounding rectangle of the connected components in the given image.
// The returned vector contains the coordinates of the bounding rectangle in the format: [x_min, y_min, x_max, y_max].
std::vector<int> mbr(const unsigned char *img, int width, int height, int channels);

#endif