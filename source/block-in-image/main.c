#include "block_detector.h"
#include "colour_detector.h"
#include "pngimport.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
	image img2 = resize_image(img, 244, 244);
	greyscale = make_grayscale(img2);

	// Use block_in_image to determine whether there is a block in the image.
	// Mask is unused because we will do nothing else other than use result.
	bool is_brick = block_in_image(greyscale);

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
