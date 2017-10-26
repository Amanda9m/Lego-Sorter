#ifndef BLOCK_DETECTOR_OPENCV_SOBEL
#define BLOCK_DETECTOR_OPENCV_SOBEL

#include "image.h"

enum sobel_filter_error_code
{
	SOBEL_FILTER_SUCCESS = 0,
	SOBEL_FILTER_OUT_OF_MEMORY,
	SOBEL_FILTER_INTERNAL_ERROR
};

/* Excecutes OpenCV's Sobel function to determine the 
   sobel filtered image given the source image.

   Preconditions:
      - source is a greyscale image { channels == 1 }
	  - output is not null { !!output }
	  - source is a valid image { source.img != NULL }
	  - source is not an empty image { source.height != 0 && source.width != 0 }

   Postconditions:
	  - output is overwritten with a new image if the
	    return code is SOBEL_FILTER_SUCCESS
	  - source is the same as before
	  - If the return code is not SOBEL_FILTER_SUCCESS
	    the state of of output is undefined

   Returns an error code that indicates whether an
   error occurred while executing the function.
*/
enum sobel_filter_error_code sobel_filter(
	const image source,
	image* output);

#endif
