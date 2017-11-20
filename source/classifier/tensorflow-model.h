
#include "image.h"

typedef struct tensorflow_model tensorflow_model;

typedef struct output_class
{
	uint32_t classId;
	double probability;
} output_class;

tensorflow_model* model_load(
	const char* filename);
void model_free(tensorflow_model* model);
 
output_class model_run(tensorflow_model* model, image img);


