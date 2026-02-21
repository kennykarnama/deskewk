#ifndef THRESHOLD_HPP
#define THRESHOLD_HPP

int threshold(unsigned char *img, int width, int height, int channels);

void segment(const unsigned char *img, unsigned char *dst, int width, int height, int channels, int threshold_value);

#endif