#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "image.h"
#include "colour.h"
#include "tensorflow-model.h"

static tensorflow_model* model = NULL;

#define MODEL_NAME "colour-detect.pb"

lego_colour colours[] = {
	{ 0, "Black", { 0, 0, 0 } },
	{ 0, "Blue",  { 0, 0, 255 } },
	{ 0, "Green", { 0, 255, 0 } },
	{ 0, "Gray",  { 128, 128, 128 } },
	{ 0, "Red",   { 255, 0, 0 } },
	{ 0, "White", { 255, 255, 255 } },
	{ 0, "Yellow",{ 255, 255, 0 } }
};

void init_colour_model()
{
	if (!model)
	{
		model = model_load(MODEL_NAME);
	}
}

lego_colour detect_colour(
	image source)
{
	assert(source.channels * source.width * source.height != 0);
	assert(source.img != 0);

	output_class output = model_run(model, source);

	return colours[output.classId];
}
