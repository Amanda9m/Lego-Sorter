
// Make sure that all C headers are parsed as C headers
// otherwise linking will fail
extern "C" {
#include "image.h"
#include "opencv-sobel.h"
}

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core.hpp"

#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstring>

/* This function is heavily inspired by this tutorial
   https://docs.opencv.org/3.2.0/d2/d2c/tutorial_sobel_derivatives.html	
*/
extern "C" sobel_filter_error_code sobel_filter(
	image source,
	image* output)
{
	// Make sure that the source image is a grayscale image
	assert(source.channels == 1);
	// Make sure that the output image is not NULL
	assert(output != NULL);

	// Ensure that the source image is valid
	assert(source.img != NULL);
	// Ensure that the source image has a size greater than 0
	assert(source.height != 0 && source.width != 0);

	try {
		// Create an OpenCV matrix holding the image
		cv::Mat src = cv::Mat(
			source.width,
			source.height,
			CV_8UC(1),
			source.img);

		cv::Mat grad_x, grad_y, abs_grad_x, abs_grad_y, grad, out;

		// Get the x and y gradiends
		cv::Sobel(src, grad_x, CV_16SC1, 1, 0);
		cv::Sobel(src, grad_y, CV_16SC1, 0, 1);

		cv::convertScaleAbs(grad_x, abs_grad_x);
		cv::convertScaleAbs(grad_y, abs_grad_y);

		cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

		output->width = source.width;
		output->height = source.height;
		output->channels = 1;

		grad.assignTo(out, CV_8UC1);

		output->img = (uint8_t*)malloc(
			source.width * source.height * sizeof(uint8_t));

		if (!output->img)
			return SOBEL_FILTER_OUT_OF_MEMORY;

		assert(out.isContinuous());

		std::memcpy(output->img, out.data,
			source.width * source.height * sizeof(uint8_t));
	} 
	catch (...)
	{
		return SOBEL_FILTER_INTERNAL_ERROR;
	}
	return SOBEL_FILTER_SUCCESS;
}
