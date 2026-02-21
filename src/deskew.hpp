#ifndef DESKEW_HPP
#define DESKEW_HPP

struct IntermediaryImageOutput {
    bool write_rotations;
    bool write_projections;
    bool write_bb;
    bool write_segmented;
    
    const char* output_dir;
};

double estimated_skew_angle(unsigned char *img, int width, int height, int channels, IntermediaryImageOutput* intermediaryOpt);

#endif