#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "image.h"
#include "colour.h"
#include "colour_detector.h"

colour detect_colour(image source, image block_mask) {
	uint8_t r = 0, g = 0, b = 0;
	int count = 0;
	int size = min(source.height*source.width, block_mask.height*block_mask.width);

	for (int j = 0; j < size; j++) {
		if (block_mask.img[j]/*image number format to be further learned*/) {
			r = r + source.img[j]/*image number format to be further learned*/;
			g = g + source.img[j]/*image number format to be further learned*/;
			b = b + source.img[j]/*image number format to be further learned*/;
			count++;
		}
	}

	r = r / count;
	g = g / count;
	b = b / count;

	colour block = { r, g, b };
	colour known = { 0, 0, 0 };

	/*Comparison to known LEGO RGB values to be added.
	  Closest value will be stored in known.*/

	return known;

	/**/
}