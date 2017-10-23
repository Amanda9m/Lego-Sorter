#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "image.h"
#include "colour.h"
#include "colour_detector.h"
#include "lego_colours.h"

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

colour find_nearest_colour(colour guess)
{
#define lego_colours_size (sizeof(lego_colours) / sizeof(struct lego_colour))
	/* For now do rgb comparisons, but if we 
	   really want to pick the nearest colour
	   visually then using a colour space that
	   is linear with the camera might give
	   better results.
	*/

	int32_t current_min = 0;
	size_t min_idx = 0;

	for (size_t i = 1; i < lego_colours_size; ++i)
	{
		const int32_t dist_r = (int32_t)lego_colours[i].rgb.r - guess.r;
		const int32_t dist_g = (int32_t)lego_colours[i].rgb.g - guess.g;
		const int32_t dist_b = (int32_t)lego_colours[i].rgb.b - guess.b;

		const int32_t result = (dist_r * dist_r) + 
			(dist_g * dist_g) + (dist_b * dist_b);

		if (result < current_min)
		{
			min_idx = i;
			current_min = result;
		}
	}

	return lego_colours[min_idx].rgb;
#undef lego_colours_size
}

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

	colour block = { (uint8_t)r, (uint8_t)g, (uint8_t)b };

	// TODO
	/*Comparison to known LEGO RGB values to be added.
	  Closest value will be stored in known.*/

	// find closest lego colour based on directed line segment norms
	colour known = find_nearest_colour(block);

	return known;

	/**/
}