#include "deskew.h"

#include <cmath>
#include <numeric>

namespace deskewk {

namespace {

constexpr double PI = 3.14159265358979323846;

double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

double toDegrees(double radians) {
    return radians * 180.0 / PI;
}

} // anonymous namespace

double estimateSkewAngle(const Image& image) {
    if (image.height == 0 || image.width == 0) {
        return 0.0;
    }

    double bestAngle = 0.0;
    double bestScore = -1.0;

    // Search over a range of candidate angles (-45 to +45 degrees)
    for (int a = -45; a <= 45; ++a) {
        double angle = toRadians(static_cast<double>(a));
        double cosA = std::cos(angle);
        double sinA = std::sin(angle);

        std::vector<int> profile(image.height, 0);
        for (int y = 0; y < image.height; ++y) {
            for (int x = 0; x < image.width; ++x) {
                int ry = static_cast<int>(x * sinA + y * cosA);
                if (ry >= 0 && ry < image.height) {
                    profile[ry] += image.pixels[y][x];
                }
            }
        }

        // Score = variance of the projection profile (higher is better)
        if (profile.empty()) { continue; }
        double mean = std::accumulate(profile.begin(), profile.end(), 0.0) / profile.size();
        double variance = 0.0;
        for (int v : profile) {
            double diff = v - mean;
            variance += diff * diff;
        }

        if (variance > bestScore) {
            bestScore = variance;
            bestAngle = static_cast<double>(a);
        }
    }

    return bestAngle;
}

Image deskew(const Image& image) {
    double angle = estimateSkewAngle(image);
    double rad = toRadians(-angle);
    double cosA = std::cos(rad);
    double sinA = std::sin(rad);

    Image result;
    result.width = image.width;
    result.height = image.height;
    result.pixels.assign(image.height, std::vector<int>(image.width, 0));

    int cx = image.width / 2;
    int cy = image.height / 2;

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int dx = x - cx;
            int dy = y - cy;
            int srcX = static_cast<int>(dx * cosA - dy * sinA) + cx;
            int srcY = static_cast<int>(dx * sinA + dy * cosA) + cy;
            if (srcX >= 0 && srcX < image.width && srcY >= 0 && srcY < image.height) {
                result.pixels[y][x] = image.pixels[srcY][srcX];
            }
        }
    }

    return result;
}

} // namespace deskewk
