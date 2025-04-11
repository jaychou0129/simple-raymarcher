//
// Created by Balajanovski on 2/04/2017.
//

#ifndef MANDELBROT_FRACTAL_DRAWER_IMAGE_BUFFER_H
#define MANDELBROT_FRACTAL_DRAWER_IMAGE_BUFFER_H

#include <string>
#include "PixelBufferBase.h"
#include "Color.h"
#include <png.h>
#include <memory>

#define PNG_DEBUG 3

class ImageBuffer : public PixelBufferBase {
private:
    // Location to write image to
    std::string file_src;
    int offset = 0; // file name offset i.e. file_src_0.png, file_src_1.png, etc.

    // PNG data
    png_structp png_ptr;
    png_infop info_ptr;


    // File pointer
    FILE *fp;
public:
    ImageBuffer(std::shared_ptr<Screen<int>>& screen_dimensions, const std::string& src);

    ~ImageBuffer();

    virtual void flush() override;
};


#endif //MANDELBROT_FRACTAL_DRAWER_IMAGE_BUFFER_H
