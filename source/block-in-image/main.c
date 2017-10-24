
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
	int err = import_image(argv[1], &img);

	if (err != 0)
	{
		printf("An error occurred while reaing '%s'", argv[1]);
		return 2;
	}

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
