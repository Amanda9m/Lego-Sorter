
#include "block_recognizer.h"

#include <stdlib.h>
#include <assert.h>

#include "tensorflow-model.h"

#define MODEL_NAME "block-model.pb"

static tensorflow_model* model = NULL;

block_type types[] = {
	{ 2, 2, 3 }, // 2x2 thick
	{ 2, 3, 3 }, // 2x3 thick
	{ 1, 4, 3 }, // 1x4 thick
	{ 1, 6, 3 }, // 1x6 thick
	{ 2, 2, 1 }, // 2x2 thin
	{ 2, 3, 1 }, // 2x3 thin
	{ 2, 4, 1 }, // 2x4 thin
	{ 4, 4, 1 }, // 4x4 thin
	{ 2, 6, 1 }, // 2x6 thin
	{ 1, 8, 3 }, // 1x8 thick
};

block_type recognize_block(image img)
{

}

