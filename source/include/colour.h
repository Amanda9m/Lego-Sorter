#ifndef COLOUR_H
#define COLOUR_H

#include <stdint.h>

typedef struct 
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} colour;

typedef struct lego_colour
{
	uint16_t lego_id;
	const char* colour_name;
	colour rgb;
} lego_colour;

#endif
