
#include "opencv-sobel.h"

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#define FILTER_SIZE 3
#define OFFSET (FILTER_SIZE/2)

#define abs16(x) ((x) < 0 ? -(x) : (x))

typedef struct
{
	const int16_t(*kernelx)[FILTER_SIZE];
	const int16_t(*kernely)[FILTER_SIZE];
	int16_t norm;
} filter_desc;

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

uint8_t pixel_at(
	const image* img,
	int64_t x,
	int64_t y,
	size_t channel)
{
	assert(channel < img->channels);

	// Clamp x
	if (x < 0)
		x = 0;
	else if ((size_t)x >= img->width)
		x = (int64_t)img->width - 1;

	// Clamp y
	if (y < 0)
		y = 0;
	else if ((size_t)y >= img->height)
		y = (int64_t)img->height - 1;

	return img->img[(size_t)y * img->width * img->channels
		+ (size_t)x * img->channels + channel];
}

uint8_t value_at(
	const filter_desc* desc,
	const image* img,
	int64_t x,
	int64_t y,
	size_t channel)
{
	assert(desc != NULL);
	assert(img != NULL);

	int32_t dx = 0, dy = 0;

	for (int32_t i = 0; i < FILTER_SIZE; ++i)
	{
		for (int32_t j = 0; j < FILTER_SIZE; ++j)
		{
			int32_t pixel = pixel_at(
				img,
				x + i - OFFSET,
				y + j - OFFSET,
				channel);

			dx += pixel * desc->kernelx[i][j];
			dy += pixel * desc->kernely[i][j];
		}
	}

	// Divide by 4 to normalize back into the range of uint8_t
	return (uint8_t)((abs16(dx) + abs16(dy)) / desc->norm);
}

void filter(
	uint8_t* output,
	const image* img,
	const filter_desc* desc)
{
	// Arguments are non-null
	assert(!!output);
	assert(!!desc);

	// Verify that desc->img is valid
	assert(img->img != NULL);
	assert(img->width * img->height * img->channels != 0);

	// Verify that desc is valid
	assert(desc->kernelx != NULL);
	assert(desc->kernely != NULL);
	assert(desc->norm != 0);

#define height (img->height)
#define width (img->width)
#define channels (img->channels)

	for (uint32_t y = 0; y < height; ++y)
	{
		for (uint32_t x = 0; x < width; ++x)
		{
			uint32_t sum = 0;

			for (uint32_t c = 0; c < channels; ++c)
			{
				sum += value_at(desc, img, x, y, c);
			}

			output[y * width + x] 
				= sum > 255 ? 255 : sum;
		}
	}

#undef height
#undef width
#undef channels
}


sobel_filter_error_code sobel_filter(
	const image source,
	image* output)
{
	filter_desc kernel = {
		kernelx,
		kernely,
		4
	};

	uint8_t *out = malloc(sizeof(uint8_t) * source.height * source.width);

	if (!out)
		return SOBEL_FILTER_OUT_OF_MEMORY;

	output->img = out;
	output->channels = 1;
	output->height = source.height;
	output->width = source.width;

	filter(out, &source, &kernel);

	return SOBEL_FILTER_SUCCESS;
}
