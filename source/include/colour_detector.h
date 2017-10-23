#ifndef COLOUR_DETECTOR_H
#define COLOUR_DETECTOR_H

#include "colour.h"
#include "image.h"

colour detect_colour(
    image source,
    image block_mask);

#endif
