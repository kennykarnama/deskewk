#ifndef CC_HPP
#define CC_HPP

#include<vector>

// mbr computes the minimum bounding rectangle of the connected components in the given image.
// The returned vector contains the coordinates of the bounding rectangle in the format: [x_min, y_min, x_max, y_max].
std::vector<int> mbr(const unsigned char *img, int width, int height, int channels);

// write_mbr_visualization draws a bold, high-contrast bounding rectangle and writes it to outpath.
// bbox format: [x_min, y_min, x_max, y_max]. Returns 0 on success, -1 on failure.
int write_mbr_visualization(const unsigned char *img,
							int width,
							int height,
							int channels,
							const std::vector<int> &bbox,
							const char *outpath);

#endif