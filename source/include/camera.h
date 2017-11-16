#ifndef CAMERA_INTERFACE_H
#define CAMERA_INTERFACE_H

#include "image.h"

typedef enum
{
	CAMERA_ERR_SUCCESS = 0,
	CAMERA_ERR_INTERNAL_ERROR,
	CAMERA_ERR_OUT_OF_MEMORY,
	CAMERA_ERR_INVALID_ARGUMENTS,

} camera_error_code;

typedef struct camera camera;

/* Takes a picture using the raspberry PI camera
   interface specified with cam.

   The output image size is controlled by the 
   camera interface and thus can only be set
   at creation time.

   This will return an error code if there is any
   error in reading an image off of the camera.
   If an error code is returned then the output
   image will be invalid.
*/
camera_error_code take_picture(
	camera* cam,
	image* output);

/* Creates a camera interface using the broadcom
   MMAL interface. If anything fails when setting
   up the camera interface (i.e. no camera, not
   enough GPU memory, etc.), this will return null.
*/
camera* create_camera(
	uint32_t y_resolution,
	uint32_t x_resolution);
/* Destroys a previously created camera interface. */
void destroy_camera(camera* cam);

#endif
