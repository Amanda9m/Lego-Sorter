#include "pngimport.h"
#include "block_detector.h"
#include "colour_detector.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

image im_mask(const image im1, const image im2)
{
	assert(im2.channels == 1);
	assert(im2.height == im1.height);
	assert(im2.width == im2.width);
	assert(im2.img);
	assert(im1.img);

	image out = {
		im1.height,
		im1.width,
		im1.channels,
		calloc(1, sizeof(uint8_t) * im1.height * im1.width * im1.channels)
	};

	for (size_t i = 0; i < im1.height * im1.width; ++i)
	{
		if (im2.img[i] < 128)
		{
			for (size_t c = 0; c < im1.channels; ++c)
			{
				size_t i1 = i * im1.channels + c;
				out.img[i1] = im1.img[i1];
			}
		}
	}

	return out;
}

image make_grayscale(image source)
{
	image out = {
		source.height,
		source.width,
		1,
		malloc(sizeof(uint8_t) * source.height * source.width)
	};

	assert(out.img != NULL);

	const size_t size = source.height * source.width;
	for (size_t i = 0; i < size; ++i)
	{
		out.img[i] = (source.img[i * 3]
			+ source.img[i * 3 + 1]
			+ source.img[i * 3 + 2]) / 3;
	}

	return out;
}


// Use a form of main that takes command line arguments
int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf(
			"Usage: block-in-image <image>\n"
			"   Outputs 'true' if it determines that a lego\n"
			"   brick is within <image>, 'false' otherwise.\n"
		);
		return 1;
	}

	image img, greyscale;

	// Load the given image off disk
	int err = import_image(argv[1], &img);

	// Check to see if an error occurred while 
	// loading the image off of disk
	if (err != 0)
	{
		printf("An error occurred while reaing '%s'", argv[1]);
		return 2;
	}

	greyscale = make_grayscale(img);

	// Use block_in_image to determine whether there 
	// is a block in the image. Mask is unused because
	// we will do nothing else other than use result.
	bool is_brick = block_in_image(img);

	if (is_brick)
	{
		printf("1\n");

		//lego_colour colour = detect_colour(img);
		//printf("Brick Colour: %s\n", colour.colour_name);
	}
	else
	{
		printf("0\n");
	}

	// Clean up all used resources
	free(img.img);
	free(greyscale.img);

	return 0;
}
