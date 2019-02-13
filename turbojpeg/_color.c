#include "turbojpeg.h"


void cmyk2gray(unsigned char* cmyk, unsigned char* out, int npixels) {
    unsigned char k, r, g, b;
    for (; npixels--; cmyk+=4, out++) {
        k = cmyk[3];
        r = k - (((unsigned char) ~cmyk[0]) * k >> 8);
        g = k - (((unsigned char) ~cmyk[1]) * k >> 8);
        b = k - (((unsigned char) ~cmyk[2]) * k >> 8);
        *out = (r*4899 + g*9617 + b*1868 + 8192) >> 14;
    }
}


void cmyk2color(unsigned char* cmyk, unsigned char* out,
                int npixels, int pixelformat) {
    unsigned char k, r, g, b;
    int out_step = tjPixelSize[pixelformat];
    r = tjRedOffset[pixelformat];
    g = tjGreenOffset[pixelformat];
    b = tjBlueOffset[pixelformat];
    for (; npixels--; cmyk+=4, out+=out_step) {
        k = cmyk[3];
        out[r] = k - (((unsigned char) ~cmyk[0])*k>>8);
        out[g] = k - (((unsigned char) ~cmyk[1])*k>>8);
        out[b] = k - (((unsigned char) ~cmyk[2])*k>>8);
    }
}
