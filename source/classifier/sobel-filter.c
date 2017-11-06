
#include "opencv-sobel.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

/*
	Horizontal Matrix:
	
	| 1  0 -1 |
	| 2  0 -2 |
	| 1  0 -1 |
	
	Vertical Matrix:
	
	|  1  2  1 |
	|  0  0  0 |
	| -1 -2 -1 |
*/
int16_t kernelx[3][3] = {
	{ -1, 0, 1 },
	{ -2, 0, 2 },
	{ -1, 0, 1 },
};
int16_t kernely[3][3] = {
	{ 1,  2,  1 },
	{ 0,  0,  0 },
	{ -1, -2, -1 },
};

/* Returns the pixel at the given coordinates
   if a coordinate is out of bounds then it 
   clamps the access to the nearest edge.
   This clamping is required to evaluate the
   edge pixels with the filter.
*/
uint8_t pixel_at(
	const image* img,
	int32_t x,
	int32_t y)
{
	// Clamp x
	if (x < 0)
		x = 0;
	else if ((uint32_t)x >= img->width)
		x = (int32_t)img->width - 1;

	// Clamp y
	if (y < 0)
		y = 0;
	else if ((uint32_t)y >= img->height)
		y = (int32_t)img->height - 1;

	return img->img[y * (int32_t)img->width + x];
}

uint8_t sobel(
	const image* img,
	int32_t x,
	int32_t y)
{
	int16_t dx = 0, dy = 0;

	for (int32_t i = -1; i < 2; ++i)
	{
		for (int32_t j = -1; j < 2; ++j)
		{
			int16_t pixel = pixel_at(
				img,
				x + i,
				y + j);

			dx += pixel * kernelx[i + 1][j + 1];
			dy += pixel * kernely[i + 1][j + 1];
		}
	}

	// Divide by 4 to normalize back into the range of uint8_t
	return (uint8_t)((abs(dx) + abs(dy)) / 4);
}

sobel_filter_error_code sobel_filter(
	const image source,
	image* output)
{
	// Ensure source image is valid
	assert(source.width != 0 && source.height != 0);
	// Ensure source image is greyscale
	assert(source.channels == 1);
	// Ensure source image is valid, some more
	assert(source.img != NULL);
	// Ensure output image is a valid pointer
	assert(output != NULL);

	// Make sure all conversions used are ok
	assert(source.width < INT32_MAX);
	assert(source.height < INT32_MAX);

	output->width = source.width;
	output->height = source.height;
	output->channels = 1;

	output->img = malloc(sizeof(uint8_t) * source.width * source.height);

	if (!output->img)
	{
		output->width = 0;
		output->height = 0;

		return SOBEL_FILTER_OUT_OF_MEMORY;
	}

	for (size_t y = 0; y < source.height; ++y)
	{
		for (size_t x = 0; x < source.width; ++x)
		{
			// Use int32_t to accomodate negative indices
			output->img[y * source.width + x] =
				sobel(&source, (int32_t)x, (int32_t)y);
		}
	}

	return SOBEL_FILTER_SUCCESS;
}
