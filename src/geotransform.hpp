#ifndef GEOTRANSFORM_HPP
#define GEOTRANSFORM_HPP

// simple_rotate rotates the source image by the given angle (in degrees) around the center.
// src: source image buffer
// dst: destination buffer (must be pre-allocated with size width*height*channels)
// width, height: source image dimensions
// channels: number of color channels
// angle: rotation angle in degrees (counter-clockwise)
void simple_rotate(const unsigned char* src, unsigned char *dst, int width, int height, int channels, double angle);

#endif