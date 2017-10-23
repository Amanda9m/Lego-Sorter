#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

typedef struct
{
    uint32_t height;
    uint32_t width;
    uint8_t channels;
    uint8_t* img;
} image;

#endif
