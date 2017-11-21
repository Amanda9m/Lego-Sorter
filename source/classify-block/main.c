
#include "block_detector.h"
#include "block_recognizer.h"
#include "colour_detector.h"
#include "pngimport.h"
#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage: classify-block <image-file>\n");
		return 1;
	}

	image img, mask;
	if (import_image(argv[1], &img) != 0)
	{
		printf("Error importing image.\n");
		return 2;
	}

	image gray = grayscaled_image(img);

	if (!block_in_image(img, &mask))
	{
		printf("No block found in image!\n");
		return 0;
	}

	block_type type = recognize_block(gray);
	lego_colour colour = detect_colour(img);

	printf("Block Detected!\n"
		"Type: %"PRIu16"x%"PRIu16"x%"PRIu16"\n"
		"Colour: %s\n",
		type.length,
		type.width,
		type.thickness,
		colour.colour_name);

	free(img.img);
	free(gray.img);

	return 0;
}
