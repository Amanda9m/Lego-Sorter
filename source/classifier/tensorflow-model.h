
#include "image.h"

typedef struct tensorflow_model tensorflow_model;

struct output_class
{
	int classId;
	double probability;
};

tensorflow_model* model_load(
	const char* filename);
void model_free(tensorflow_model* model);
 
output_class model_run(tensorflow_model* model, image img);


