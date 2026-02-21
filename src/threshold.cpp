#include "threshold.hpp"
#include<iostream>

// threshold finds threshold value using otsu
// ref: https://www.ipol.im/pub/art/2016/158/article_lr.pdf
int threshold(unsigned char *img, int width, int height, int channels)
{
    if (channels != 1) {
        std::cerr << "Error: threshold function only supports grayscale images (1 channel)." << std::endl;

        return -1;
    }

    int dim = width * height;

    // calculate the histograms of the image
    // make sure the image is 8bit depth

    int hist[256] = {0};

    for (int i = 0; i < dim; i++){
        uint p = img[i];

        if (p > 255) {
            std::cerr << "Error: pixel value out of range (0-255)." << std::endl;
            return -1;  
        }

        hist[p]++;
    }

    long long int sum = 0;

    for (int i = 0; i < 256; i++) {
        sum += i * hist[i];
    }

    long long q1 = 0;
    long long q2 = 0;
    int threshold_value = 0;
    double max_var = 0.0;
    long long sumB = 0;


    for (int i = 0; i < 256; i++) {
        q1 += hist[i];

        if (q1 == 0) {
            continue;
        }

        q2 = dim - q1;

        if (q2 == 0) {
            break;
        }

        sumB += i * hist[i];

        long long sumDiff = sum - sumB;

        double m1 = (double)sumB / q1;
        double m2 = (double)sumDiff / q2;

        double var = q1 * q2 * (m1 - m2) * (m1 - m2);

        if (var > max_var) {
            max_var = var;
            threshold_value = i;
        }        
    }

    return threshold_value;
}

void segment(const unsigned char *img, unsigned char *dst, int width, int height, int channels, int threshold_value)
{
    if (channels != 1) {
        std::cerr << "Error: segment function only supports grayscale images (1 channel)." << std::endl;
        return;
    }

    int dim = width * height;

    for (int i = 0; i < dim; i++) {
        dst[i] = img[i] > threshold_value ? 255 : 0;
    }
}
