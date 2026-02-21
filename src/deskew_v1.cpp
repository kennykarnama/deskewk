#include "deskew.hpp"
#include "v1proc.hpp"
#include <iostream>
#include <cmath>

// estimated_skew_angle based on this paper:
// https://users.iit.demokritos.gr/~bgat/ICDAR2011_skew.pdf
// https://www.sciencepubco.com/index.php/ijet/article/view/29001
double estimated_skew_angle(unsigned char *img, int width, int height, 
    int channels, IntermediaryImageOutput* intermediaryOpt){
        
    double theta = 0.0;

    if (channels > 1) {
        unsigned char *gray_img = new unsigned char[width * height];
        rgb_to_grayscale(img, gray_img, width, height, channels);
        img = gray_img;
        channels = 1;
    }

    // threshold using otsu
    int thresh = threshold(img, width, height, channels);
    std::cout << "Otsu's threshold value: " << thresh << std::endl;

    std::cout << "segmenting image based on the threshold" << std::endl;
    unsigned char *segmented_img = new unsigned char[width * height];
    segment(img, segmented_img, width, height, channels, thresh);

    std::vector<int> bb = mbr(segmented_img, width, height, channels);
    if (bb.size() != 4) {
        std::cerr << "failed to compute bounding box for connected components" << std::endl;

        return 0.0;
    }
    
    std::cout << "Bounding box for connected components: [x_min: " << bb[0] << ", y_min: " << bb[1] << ", x_max: " << bb[2] << ", y_max: " << bb[3] << "]" << std::endl;


    double deg = -10;

    double max_energy = -std::numeric_limits<double>::max();

    while(deg <= 50) {

        if (deg == 0) {
            deg++;
        }
        
        unsigned char *rotated_img = new unsigned char[width * height * channels];
        simple_rotate(segmented_img, rotated_img, width, height, channels, deg);
        
        if (intermediaryOpt != nullptr && intermediaryOpt->write_rotations) {
            char filename[256];
            snprintf(filename, sizeof(filename), "%s/rotation_%.1f.png", 
                     intermediaryOpt->output_dir, deg);
            if (write_png_image(filename, rotated_img, width, height, channels) != 0) {
                std::cerr << "Failed to write rotated image: " << filename << std::endl;
            }
        }
        
        std::vector<int> rotated_verproj = vertical_projection(rotated_img, width, height, channels);
        double energy = 0.0;
        for (int v : rotated_verproj) {
            long long v_ll = static_cast<long long>(v);
            energy += static_cast<double>(v_ll * v_ll);
        }

        double area = static_cast<double>((bb[2] - bb[0]) * (bb[3] - bb[1]));
        if (area <= 0.0) {
            area = 1.0;
        }

        double distributionOfEnergy = energy / (0.3 * area);

        if (distributionOfEnergy > max_energy) {
            max_energy = distributionOfEnergy;
            theta = deg;
        }

        delete[] rotated_img;
        deg += 1;
    }

    delete[] segmented_img;

    return theta;

}