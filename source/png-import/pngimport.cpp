extern "C" {
#include "pngimport.h"
}

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"

#include <cstdlib>

extern "C" int import_image(
	const char* filename,
	image* output)
{
	if (!output || !filename)
		return 1;

	//try
	//{
		cv::Mat img = cv::imread(filename);
		img.convertTo(img, CV_8UC1);

		output->height = img.rows;
		output->width = img.cols;
		output->channels = img.channels();
		output->img = (uint8_t*)malloc(sizeof(uint8_t)
			* output->height * output->width * output->channels);

		if (!output->img)
			return 2;

		size_t idx = 0;
		for (size_t y = 0; y < img.rows; ++y)
		{
			for (size_t x = 0; x < img.cols; ++x)
			{
				cv::Vec<uint8_t, 3> vt = 
					img.at<cv::Vec<uint8_t, 3>>((int)y, (int)x);

				for (size_t i = 0; i < output->channels; ++i)
				{
					output->img[idx * 3 + output->channels - 1 - i] = vt[i];
				}

				idx++;
			}
		}

		return 0;
	//}
	//catch (...)
	//{
	//	// If there was an error cleanup to ensure as few 
	//	// memory leaks as possible.
	//	free(output->img);
	//
	//	/* If any C++ code throws an unexpected exception
	//	   catch it and indicate that there was an error
	//	   by returning -1. If a C++ exception propagates
	//	   up into C code then the program will crash
	//	   with no information given.
	//	*/
	//	return -1;
	//}
}
