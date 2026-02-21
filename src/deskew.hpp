#ifndef DESKEW_HPP
#define DESKEW_HPP

struct IntermediaryImageOutput {
    const char* segmentedOut;
    const char* horProjOut;
    const char* verProjOut;
    const char* mbr;
    bool write_rotations;
    const char* output_dir;
};

double estimated_skew_angle(unsigned char *img, unsigned char *out, int width, int height, int channels, IntermediaryImageOutput* intermediaryOpt);

#endif