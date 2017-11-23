
#include "tensorflow-model.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tensorflow/c/c_api.h"

// Size of an array
#define asize(a) (sizeof(a) / sizeof(a[0]))

void free_buffer(void* data, size_t length) {
	free(data);
}
void deallocate(void* data, size_t a, void* b)
{
	free(data);
}

TF_Buffer* read_file(const char* file) {
	FILE *f = fopen(file, "rb");

	if (!f)
	{
		printf("Failed to load file %s!\n", file);
		assert(0);
	}

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);                                            

	void* data = malloc(fsize);
	fread(data, fsize, 1, f);
	fclose(f);

	TF_Buffer* buf = TF_NewBuffer();
	buf->data = data;
	buf->length = fsize;
	buf->data_deallocator = free_buffer;
	return buf;
}

float* make_float_buffer(image img)
{
	size_t size = (size_t)img.height * img.width * img.channels;
	float* out = (float*)malloc(size * sizeof(float));

	for (size_t i = 0; i < size; ++i)
	{
		out[i] = (float)img.img[i] / 255.0f;
	}

	return out;
}

float* max_elem(float* begin, size_t size)
{
	assert(size != 0);

	float* max = begin;
	float* end = begin + size;
	for (float* it = begin; it != end; ++it)
		if (*begin > *max)
			max = begin;

	return max;
}

struct tensorflow_model
{
	TF_Session* session;
	TF_Graph* graph;
};

output_class model_run(
	tensorflow_model* model,
	image input)
{
	printf("%d %d %d\n", (int)input.width, (int)input.height, (int)input.channels);

	assert(input.width == 224 
		&& input.height == 224);

	printf("Run Model %p\n", model);
	assert(model);

	int64_t dims[] = { 1, input.width, input.height, input.channels };
	float* buf = make_float_buffer(input);
	size_t size = (size_t)input.height * input.width * input.channels;

	printf("Created buffer %p\n", buf);

	TF_Tensor* in = TF_NewTensor(
		TF_FLOAT,
		dims,
		asize(dims),
		buf,
		size * sizeof(float),
		deallocate,
		NULL);

	printf("Created tensor %p\n", in);

	TF_Tensor* out;
	TF_Status* status = TF_NewStatus();
	TF_Operation* in_op = TF_GraphOperationByName(model->graph, "input");
	TF_Operation* out_op = TF_GraphOperationByName(model->graph, "final_result");

	printf("Got Operations %p %p %p %p\n", out, status, in_op, out_op);

	TF_Output inputs[] = {
		{ in_op, 0 }
	};
	TF_Output outputs[] = {
		{ out_op, 0 }
	};
	const TF_Operation* const_out_op = out_op;
	
	TF_SessionRun(
		model->session,
		NULL,
		inputs, &in, 1,
		outputs, &out, 1,
		&const_out_op, 1,
		NULL, status);

	if (TF_GetCode(status) != TF_OK)
	{
		printf("ERROR: Unable to run graph %s", TF_Message(status));
		exit(-1);
	}

	size_t bufsize = TF_TensorByteSize(out) / sizeof(float);
	float* outputdata = (float*)TF_TensorData(out);

	output_class outclass = {
		.classId = max_elem(outputdata, bufsize) - outputdata
	};

	printf("Model Create Ended");

	return outclass;
}

tensorflow_model* model_load(const char* filename)
{
	tensorflow_model* model = malloc(sizeof(tensorflow_model));
	printf("Created Model %p %s\n", model, filename);
	assert(model);


	model->graph = TF_NewGraph();

	TF_Buffer* graph_def = read_file(filename);
	TF_Status* status = TF_NewStatus();
	TF_ImportGraphDefOptions* opts = TF_NewImportGraphDefOptions();

	printf("%p %p %p\n", graph_def, status, opts);

	TF_GraphImportGraphDef(
		model->graph, 
		graph_def,
		opts,
		status);

	TF_DeleteImportGraphDefOptions(opts);

	if (TF_GetCode(status) != TF_OK)
	{
		printf("ERROR: Unable to import graph %s", TF_Message(status));
		exit(-1);
	}

	TF_SessionOptions* sessopts = TF_NewSessionOptions();
	model->session = TF_NewSession(model->graph, sessopts, status);

	if (TF_GetCode(status) != TF_OK)
	{
		printf("ERROR: Unable to import graph %s", TF_Message(status));
		exit(-1);
	}

	TF_DeleteStatus(status);
	TF_DeleteBuffer(graph_def);
	TF_DeleteSessionOptions(sessopts);

	printf("Model Load Ended\n");
	return model;
}

void model_free(tensorflow_model* model)
{
	assert(model);

	TF_CloseSession(model->session, NULL);
	TF_DeleteGraph(model->graph);
	free(model);
}

