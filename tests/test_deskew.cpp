#include <gtest/gtest.h>
#include "deskew.h"

using namespace deskewk;

TEST(DeskewTest, EmptyImageReturnsZeroAngle) {
    Image img;
    img.width = 0;
    img.height = 0;
    EXPECT_DOUBLE_EQ(estimateSkewAngle(img), 0.0);
}

TEST(DeskewTest, HorizontalLineHasNearZeroAngle) {
    Image img;
    img.width = 20;
    img.height = 20;
    img.pixels.assign(img.height, std::vector<int>(img.width, 0));
    for (int x = 0; x < img.width; ++x) {
        img.pixels[10][x] = 1;
    }
    double angle = estimateSkewAngle(img);
    EXPECT_NEAR(angle, 0.0, 5.0);
}

TEST(DeskewTest, DeskewPreservesImageSize) {
    Image img;
    img.width = 10;
    img.height = 10;
    img.pixels.assign(img.height, std::vector<int>(img.width, 0));
    for (int x = 0; x < img.width; ++x) {
        img.pixels[5][x] = 1;
    }
    Image result = deskew(img);
    EXPECT_EQ(result.width, img.width);
    EXPECT_EQ(result.height, img.height);
}
