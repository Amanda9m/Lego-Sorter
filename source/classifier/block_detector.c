#include "opencv-sobel.h"
#include "pngimport.h"
#include "tensorflow-model.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MODEL_NAME "block-detect.pb"
#define BLOCK_ID 1

static tensorflow_model* model = NULL;

// Method stub for block_in_image
bool block_in_image(image source)
{
	//fprintf(stderr, "Block in Image\n");
	/* It doesn't really make sense to check if there is a block in an empty image.
	   Just returning false is an option, but for now this method will just
	     assert to ensure that the image isn't empty.
	*/
	assert(source.height != 0 && source.width != 0);

	// block_in_image requires that the image be greyscale
	//assert(source.channels == 1);

	// Require that the source image be a valid image.
	assert(source.img != NULL);

	if (!model)
		model = model_load(MODEL_NAME);

	output_class output = model_run(model, source);

	return output.classId == BLOCK_ID;
}
