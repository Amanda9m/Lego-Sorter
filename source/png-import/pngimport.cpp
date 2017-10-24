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

	try
	{
		cv::Mat img = cv::imread(filename);

		output->height = img.rows;
		output->width = img.cols;
		output->channels = img.channels();
		output->img = (uint8_t*)malloc(sizeof(uint8_t)
			* output->height * output->width * output->channels);

		if (!output->img)
			return 2;

		size_t idx = 0;
		for (size_t y = 0; y < output->height; ++y)
		{
			for (size_t x = 0; x < output->width; ++x)
			{
				for (size_t i = 0; i < output->channels; ++i)
				{
					output->img[idx * 3 + output->channels - 1 - i]
						= img.at<uint8_t>(x, y, i);
				}

				idx++;
			}
		}

		return 0;
	}
	catch (...)
	{
		return -1;
	}
}
