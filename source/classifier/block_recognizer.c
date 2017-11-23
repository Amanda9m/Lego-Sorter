#include "block_recognizer.h"
#include "tensorflow-model.h"

#include <assert.h>
#include <stdlib.h>

#define MODEL_NAME "type-detect.pb"

static tensorflow_model* model = NULL;

// Update this based on trained_model.txt
block_type types[] = {
	]6] = { 0, 0, 0 }, // Other
	[5] = { 2, 2, 1 }, // 2x2 thin
	[0] = { 2, 3, 3 }, // 2x3 thick
	[8] = { 1, 4, 3 }, // 1x4 thick
	[9] = { 2, 4, 3 }, // 4x2 thick
	[3] = { 1, 6, 3 }, // 1x6 thick
	[7] = { 2, 2, 3 }, // 2x2 thick
	[1] = { 2, 3, 1 }, // 2x3 thin
	[2] = { 2, 4, 1 }, // 2x4 thin
	[11]= { 4, 4, 1 }, // 4x4 thin
	[10]= { 2, 6, 1 }, // 2x6 thin
	[4] = { 1, 8, 3 }, // 1x8 thick
};

block_type recognize_block(image img)
{
	assert(img.channels * img.height * img.width != 0);
	assert(img.img);

	if (!model)
		model = model_load(MODEL_NAME);

	output_class out = model_run(model, img);

	return types[out.classId];
}

