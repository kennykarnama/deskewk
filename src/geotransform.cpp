#include "geotransform.hpp"

#include <cmath>
#include <algorithm>

void simple_rotate(const unsigned char* src, unsigned char *dst, int width, int height, int channels, double angle)
{
    if (src == nullptr || dst == nullptr || width <= 0 || height <= 0 || channels <= 0) {
        return;
    }

    const double angle_rad = angle * M_PI / 180.0;
    const double cos_angle = std::cos(angle_rad);
    const double sin_angle = std::sin(angle_rad);

    const double cx = width / 2.0;
    const double cy = height / 2.0;

    std::fill(dst, dst + width * height * channels, 255);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            const double x_centered = x - cx;
            const double y_centered = y - cy;

            const double src_x = x_centered * cos_angle + y_centered * sin_angle + cx;
            const double src_y = -x_centered * sin_angle + y_centered * cos_angle + cy;

            const int x0 = static_cast<int>(std::floor(src_x));
            const int y0 = static_cast<int>(std::floor(src_y));
            const int x1 = x0 + 1;
            const int y1 = y0 + 1;

            if (x0 >= 0 && x1 < width && y0 >= 0 && y1 < height) {
                
                const double fx = src_x - x0;
                const double fy = src_y - y0;
                const double fx1 = 1.0 - fx;
                const double fy1 = 1.0 - fy;

                const size_t idx00 = (static_cast<size_t>(y0) * width + static_cast<size_t>(x0)) * channels;
                const size_t idx01 = (static_cast<size_t>(y0) * width + static_cast<size_t>(x1)) * channels;
                const size_t idx10 = (static_cast<size_t>(y1) * width + static_cast<size_t>(x0)) * channels;
                const size_t idx11 = (static_cast<size_t>(y1) * width + static_cast<size_t>(x1)) * channels;
                const size_t dst_idx = (static_cast<size_t>(y) * width + static_cast<size_t>(x)) * channels;

                for (int c = 0; c < channels; ++c) {
                    const double val = fy1 * (fx1 * src[idx00 + c] + fx * src[idx01 + c]) +
                                      fy * (fx1 * src[idx10 + c] + fx * src[idx11 + c]);
                    dst[dst_idx + c] = static_cast<unsigned char>(std::clamp(val, 0.0, 255.0));
                }
            }
        }
    }
}