#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "colour.h"
#include "image.h"
#include "tensorflow-model.h"

static tensorflow_model* model = NULL;

#define MODEL_NAME "colour-detect.pb"

lego_colour colours[] = {
	[5] = { 7, "Black", { 0, 0, 0 } },
	[1] = { 3, "Green", { 0, 255, 0 } },
	[4] = { 4, "Blue",  { 0, 0, 255 } },
	[0] = { 6, "Gray",  { 128, 128, 128 } },
	[2] = { 1, "Red",   { 255, 0, 0 } },
	[3] = { 5, "White", { 255, 255, 255 } },
	[6] = { 2, "Yellow",{ 255, 255, 0 } }
};

lego_colour detect_colour(
	image source)
{
	assert(source.channels * source.width * source.height != 0);
	assert(source.img != 0);

	if (!model)
		model = model_load(MODEL_NAME);

	output_class output = model_run(model, source);

	return colours[output.classId];
}
