#include "cc.hpp"

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
                if (img[idx + c] > 0) {
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