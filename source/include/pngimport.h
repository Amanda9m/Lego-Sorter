#ifndef PNGIMPORT_H
#define PNGIMPORT_H

#include "image.h"

/* Uses OpenCV's image import functions to read
   in an image from the filesystem and convert
   it to an actual image.

   Return Values:
   0: The image was loaded successfully
   1: An argument was null
   2: Unable to allocate memory for the image
   -1: If an unknown error occurred.
*/
int import_image(
	const char* filename,
	image* output);

#endif
