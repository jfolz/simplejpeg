#ifndef SIMPLEJPEG_COLOR_H
#define SIMPLEJPEG_COLOR_H
void cmyk2gray(unsigned char* cmyk, unsigned char* out, int npixels);
void cmyk2color(unsigned char* cmyk, unsigned char* out, int npixels, int pixelformat);
#endif
