
extern "C" {
#include "tensorflow-model.h"
}

#include "opencv2/dnn.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <cassert>

struct tensorflow_model
{
	cv::dnn::Net net;
};

extern "C" tensorflow_model* model_load(
	const char* filename)
{
	tensorflow_model* model = new tensorflow_model;

	model->net = cv::dnn::readNetFromTensorflow(filename);

	return model;
}
extern "C" void model_free(
	tensorflow_model* model)
{
	delete model;
}

extern "C" output_class model_run(
	tensorflow_model* model, 
	image img)
{
	assert(model && img);

	int type = CV_MAKETYPE(CV_8U, img.channels);
	cv::Mat mat = cv::Mat(img.height, img.width, type, img.img);
	cv::Mat in_blob = cv::dnn::blobFromImage(mat);

	model->net.setInput(in_blob);

	cv::Mat out = model->net.forward();

	output_class output;

	cv::Mat prob_mat = out.reshape(1, 1);
	cv::Point class_number;

	cv::minMaxLoc(
		prob_mat, 
		NULL, 
		&output.probability, 
		NULL,
		&class_number);

	output.classId = class_number.x;

	return output;
}
