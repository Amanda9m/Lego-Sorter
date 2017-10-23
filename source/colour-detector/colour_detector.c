#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "image.h"
#include "colour.h"
#include "colour_detector.h"

/* This macro will access the given element 
   at the pixel with element index.

   The way that it works is as follows:
   index is the pixel index, the pixel
   starts at index * src.channels, the next
   src.channels elements are the colours of
   the pixel.
*/
#define img_pixel(src, index, channel) ((src).img[(index) * (src).channels + (channel)])

/* Mask pixels with a value above 128 are considered
   to be part of the lego block. This value can be 
   changed later to better suit what should be considered
   the lego block.
*/
#define edge_threshold 128

colour detect_colour(image source, image block_mask) {
	// source and block_mask must have the same sizes
	assert(source.width == block_mask.width);
	assert(source.height == block_mask.height);

	// source and block_mask must be valid images
	assert(source.img != NULL);
	assert(block_mask.img != NULL);

	// source must have 3 channels (r, g, b)
	assert(source.channels == 3);
	// block_mask must have 1 channel
	assert(block_mask.channels == 1);

	uint32_t r = 0, g = 0, b = 0;
	size_t count = 0;
	const size_t size = source.height * source.width;
	

	for (size_t j = 0; j < size; j++) {
		if (img_pixel(block_mask, j, 0) > edge_threshold) {
			r += img_pixel(source, j, 0);
			g += img_pixel(source, j, 1);
			b += img_pixel(source, j, 2);
			count++;
		}
	}

	r /= count;
	g /= count;
	b /= count;

	colour block = { r, g, b };
	colour known = { 0, 0, 0 };

	// TODO
	/*Comparison to known LEGO RGB values to be added.
	  Closest value will be stored in known.*/

	return known;

	/**/
}