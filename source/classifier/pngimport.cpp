extern "C" {
#include "pngimport.h"
}

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <cstdlib>

extern "C" int import_image(
	const char* filename,
	image* output)
{
	if (!output || !filename)
		return 1;

	try
	{
		cv::Mat img = cv::imread(filename);
		img.convertTo(img, CV_8UC1);
		//cv::cvtColor(img, img, CV_RGB2BGR);

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
					img.at<cv::Vec<uint8_t, 3> >((int)y, (int)x);

				for (size_t i = 0; i < output->channels; ++i)
				{
					output->img[idx * 3 + output->channels - 1 - i] = vt[(int)i];
				}

				idx++;
			}
		}

		return 0;
	}
	catch (...)
	{
		// If there was an error, cleanup to ensure as few 
		// memory leaks as possible.
		free(output->img);

		/* If any C++ code throws an unexpected exception
		   catch it and indicate that there was an error
		   by returning -1. If a C++ exception propagates
		   up into C code then the program will crash
		   with no information given.
		*/
		return -1;
	}
}

extern "C" int debug_export(
	image img,
	const char* filename)
{
	// Create an OpenCV image with the same number of channels
	// as in the source image
	int type = CV_MAKETYPE(CV_8U, img.channels);
	cv::Mat mat = cv::Mat(img.height, img.width, type, img.img);
	// If we have 3 channels, swap the R and B channels as 
	// otherwise yellow bricks become blue
	if (img.channels == 3)
		cv::cvtColor(mat, mat, CV_RGB2BGR);
	cv::imwrite(filename, mat);

	return 0;
}

extern "C" image resize_image(
	image img,
	uint32_t nwidth,
	uint32_t nheight)
{
	printf("%d %d\n", (int)nwidth, (int)nheight);

	int type = CV_MAKETYPE(CV_8U, img.channels);
	cv::Mat mat = cv::Mat(img.height, img.width, type, img.img);
	cv::Mat outmat = cv::Mat(nheight, nwidth, type);

	cv::resize(mat, outmat, cv::Size((int)nwidth, (int)nheight));

	image out = {
		nheight,
		nwidth,
		img.channels,
		(uint8_t*)malloc(sizeof(uint8_t) * nheight *
			nwidth * img.channels)
	};

	memcpy(out.img, outmat.data,
		sizeof(uint8_t) * nheight *	nwidth * img.channels);

	return out;
}
