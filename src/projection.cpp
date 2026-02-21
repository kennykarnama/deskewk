#include "projection.hpp"

#include <algorithm>
#include <vector>

#include "stb_image_write.h"

std::vector<int> horizontal_projection(const unsigned char *img, int width, int height, int channels)
{
    std::vector<int> projection(height, 0);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width * channels + x * channels;
            bool is_black = true;
            for (int c = 0; c < channels; ++c) {
                if (img[idx + c] > 0) {
                    is_black = false;
                    break;
                }
            }
            if (is_black) {
                projection[y]++;
            }
        }
    }
    
    return projection;
}

int write_horizontal_projection_image(const std::vector<int> &projection, int image_width, const char *outpath)
{
    if (projection.empty() || image_width <= 0 || outpath == nullptr) {
        return -1;
    }

    const int height = static_cast<int>(projection.size());
    const int width = image_width;
    const int channels = 1;

    int max_value = *std::max_element(projection.begin(), projection.end());
    if (max_value <= 0) {
        max_value = 1;
    }

    std::vector<unsigned char> img(static_cast<size_t>(width * height), 255);

    for (int y = 0; y < height; ++y) {
        const int bar_len = static_cast<int>((static_cast<long long>(projection[y]) * width) / max_value);
        for (int x = 0; x < bar_len; ++x) {
            img[y * width + x] = 0;
        }
    }

    const int stride = width * channels;
    int success = stbi_write_png(outpath, width, height, channels, img.data(), stride);
    return success ? 0 : -1;
}

std::vector<int> vertical_projection(const unsigned char *img, int width, int height, int channels)
{
    std::vector<int> projection(width, 0);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int idx = y * width * channels + x * channels;
            bool is_black = true;
            for (int c = 0; c < channels; ++c) {
                if (img[idx + c] > 0) {
                    is_black = false;
                    break;
                }
            }
            if (is_black) {
                projection[x]++;
            }
        }
    }
    
    return projection;
}

int write_vertical_projection_image(const std::vector<int> &projection, int image_height, const char *outpath)
{
    if (projection.empty() || image_height <= 0 || outpath == nullptr) {
        return -1;
    }

    const int width = static_cast<int>(projection.size());
    const int height = image_height;
    const int channels = 1;

    int max_value = *std::max_element(projection.begin(), projection.end());
    if (max_value <= 0) {
        max_value = 1;
    }

    std::vector<unsigned char> img(static_cast<size_t>(width * height), 255);

    for (int x = 0; x < width; ++x) {
        const int bar_len = static_cast<int>((static_cast<long long>(projection[x]) * height) / max_value);
        for (int y = height - 1; y >= height - bar_len; --y) {
            img[y * width + x] = 0;
        }
    }

    const int stride = width * channels;
    int success = stbi_write_png(outpath, width, height, channels, img.data(), stride);
    return success ? 0 : -1;
}  