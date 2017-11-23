#include "image.h"

#include <assert.h>
#include <stdlib.h>

static uint8_t* pixel_at_impl(
	image src, 
	size_t x, 
	size_t y, 
	size_t c)
{
	assert(x < src.width);
	assert(y < src.height);
	assert(c < src.channels);

	return &src.img[y * src.width * src.channels + x * src.channels + c];
}

// Accesses a pixel element at (x, y) and gives the channel component
#define img_pixel_at(src, x, y, channel) (*pixel_at_impl((src), (x), (y), (channel)))

image grayscaled_image(image in)
{
	image out = {
		.height   = in.height,
		.width    = in.width,
		.channels = in.channels,
		.img      = NULL
	};

	// Make sure image is valid
	assert(in.height != 0
		&& in.width != 0
		&& in.channels != 0
		&& in.img != NULL);

	out.img = malloc(in.height * in.width * in.channels * sizeof(uint8_t));
	assert(out.img != NULL);

	for (uint32_t y = 0; y < in.height; ++y)
	{
		for (uint32_t x = 0; x < in.width; ++x)
		{
			uint16_t sum = 0;

			for (uint8_t c = 0; c < in.channels; ++c)
				sum += img_pixel_at(in, x, y, c);

			sum = sum / in.channels;

			for (uint8_t c = 0; c < in.channels; ++c)
				img_pixel_at(out, x, y, c) = sum;
		}
	}

	return out;
}
