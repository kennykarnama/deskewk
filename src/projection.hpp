#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include <vector>

std::vector<int> horizontal_projection(const unsigned char *img, int width, int height, int channels);
int write_horizontal_projection_image(const std::vector<int> &projection, int image_width, const char *outpath);

std::vector<int> vertical_projection(const unsigned char *img, int width, int height, int channels);
int write_vertical_projection_image(const std::vector<int> &projection, int image_height, const char *outpath);

#endif