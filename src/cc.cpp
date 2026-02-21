#include "cc.hpp"
#include "io.hpp"

#include <algorithm>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/multi_point.hpp>
#include <boost/geometry/geometries/point.hpp>

std::vector<int> mbr(const unsigned char *img, int width, int height, int channels)
{
    if (img == nullptr || width <= 0 || height <= 0 || channels <= 0) {
        return {};
    }

    namespace bg = boost::geometry;
    using point_t = bg::model::point<int, 2, bg::cs::cartesian>;
    using mpoint_t = bg::model::multi_point<point_t>;
    using box_t = bg::model::box<point_t>;

    mpoint_t points;
    points.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const int idx = (y * width + x) * channels;
            bool foreground = false;
            for (int c = 0; c < channels; ++c) {
                // treat black pixels (0) as foreground (text) since segmentation
                // produces 0 for foreground and 255 for background
                if (img[idx + c] == 0) {
                    foreground = true;
                    break;
                }
            }
            if (foreground) {
                points.push_back(point_t(x, y));
            }
        }
    }

    if (points.empty()) {
        return {};
    }

    box_t box;
    bg::envelope(points, box);

    const int x_min = bg::get<bg::min_corner, 0>(box);
    const int y_min = bg::get<bg::min_corner, 1>(box);
    const int x_max = bg::get<bg::max_corner, 0>(box);
    const int y_max = bg::get<bg::max_corner, 1>(box);

    return {x_min, y_min, x_max, y_max};
}

int write_mbr_visualization(const unsigned char *img,
                            int width,
                            int height,
                            int channels,
                            const std::vector<int> &bbox,
                            const char *outpath)
{
    if (img == nullptr || outpath == nullptr || width <= 0 || height <= 0 || channels <= 0) {
        return -1;
    }
    if (bbox.size() != 4) {
        return -1;
    }

    int x_min = std::clamp(bbox[0], 0, width - 1);
    int y_min = std::clamp(bbox[1], 0, height - 1);
    int x_max = std::clamp(bbox[2], 0, width - 1);
    int y_max = std::clamp(bbox[3], 0, height - 1);
    if (x_min > x_max || y_min > y_max) {
        return -1;
    }

    const int out_channels = 3;
    std::vector<unsigned char> out(static_cast<size_t>(width) * static_cast<size_t>(height) * static_cast<size_t>(out_channels));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const size_t src_idx = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x)) * static_cast<size_t>(channels);
            const size_t dst_idx = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x)) * static_cast<size_t>(out_channels);
            if (channels == 1) {
                const unsigned char v = img[src_idx];
                out[dst_idx + 0] = v;
                out[dst_idx + 1] = v;
                out[dst_idx + 2] = v;
            } else {
                out[dst_idx + 0] = img[src_idx + 0];
                out[dst_idx + 1] = img[src_idx + 1];
                out[dst_idx + 2] = img[src_idx + 2];
            }
        }
    }

    auto set_pixel_red = [&](int x, int y) {
        size_t idx = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x)) * static_cast<size_t>(out_channels);
        out[idx + 0] = 255;
        out[idx + 1] = 0;
        out[idx + 2] = 0;
    };

    const int thickness = 3;
    for (int t = -thickness; t <= thickness; ++t) {
        int y_top = std::clamp(y_min + t, 0, height - 1);
        int y_bot = std::clamp(y_max + t, 0, height - 1);
        for (int x = x_min; x <= x_max; ++x) {
            set_pixel_red(x, y_top);
            set_pixel_red(x, y_bot);
        }

        int x_left = std::clamp(x_min + t, 0, width - 1);
        int x_right = std::clamp(x_max + t, 0, width - 1);
        for (int y = y_min; y <= y_max; ++y) {
            set_pixel_red(x_left, y);
            set_pixel_red(x_right, y);
        }
    }

    return write_png_image(outpath, out.data(), width, height, out_channels);
} 