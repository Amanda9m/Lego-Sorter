
#include <stdint.h>

#include "image.h"

typedef struct block_type
{
	uint16_t width;
	uint16_t length;
	uint16_t thickness;
} block_type;

block_type recognize_block(image img);
