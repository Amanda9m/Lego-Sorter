
#include "pngimport.h"
#include "block_detector.h"

#include <stdio.h>
#include <stdlib.h>

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

	image img, mask = { .img = NULL };

	// Load the given image off disk
	int err = import_image(argv[1], &img);

	// Check to see if an error occurred while 
	// loading the image off of disk
	if (err != 0)
	{
		printf("An error occurred while reaing '%s'", argv[1]);
		return 2;
	}

	// Use block_in_image to determine whether there 
	// is a block in the image. Mask is unused because
	// we will do nothing else other than use result.
	bool is_brick = block_in_image(img, &mask);

	if (is_brick)
	{
		printf("true\n");
	}
	else
	{
		printf("false\n");
	}

	// Clean up all used resources
	free(img.img);
	free(mask.img);

	return 0;
}
