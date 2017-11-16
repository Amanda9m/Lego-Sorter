
#include "camera.h"
#include "pngimport.h"

/*
Basic Approach:
  I tried to setup a way for the camera to take
  pictures using the MMAL interface to do it all
  directly from within the program. That proved
  to be far too hard and MMAL has basically 0
  pages of actually useful documentation across
  all of the internet.

  Anyway, the way this code works is it starts an
  instance of raspistill in signal mode. That is
  raspistill waits to receive a signal then takes
  a picture. So we just set raspistill to write 
  to a known location every time then read it out.
  Most of the code here is just dealing with 
  starting another process and finding its PID so
  that we can send signals to it.

  Another thing is that it takes too long for the
  camera to take a picture after sending the signal.
  (I think, I haven't tested this.) The resolution
  to this is to use the image taken by the previous
  signal then send a new one after reading the 
  image.
*/

// C headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

// Linux headers
#include <unistd.h>
#include <signal.h>
#include <sys\types.h>

#define MAX_UINT32_OUTPUT_SIZE 10

struct camera
{
	// The PID of the raspistill process
	pid_t pid;
	FILE* stream;
	// Note this is allocated using the same
	// same memory as the camera struct
	char* tmpdir;
	uint32_t width;
	uint32_t height;
};

static const char temp_name[] = "/camout.jpg";
// Command template for raspistill
static const char command_template[] = "raspistill " 
	"-t 0 "         // Keep running forever
	"-s "           // Enable signal mode (takes picture when receiving a signal)
	"-n "           // Disable preview
	"-vf "          // Vertical flip
	"-ss 100000 "   // Set shutter speed to 0.1 ms
	"-q 100 "       // Set JPEG quality to maximum
	"-w %"PRIu32" " // Set image width to desired width  
	"-h %"PRIu32" " // Set image height to desired height
	"-o %s "        // Set output filename
;



/* Uses the pidof program to find the PID of the given program */
pid_t get_pid(char* commandname)
{
	char line[1024];

	snprintf(line, 1024, "pidof %s", commandname);

	FILE* cmd = popen(line, "r");
	// The first line from the output
	fgets(line, sizeof(line), cmd);
	pclose(cmd);
	
	// Parse the output to find the PID
	return strtol(line, NULL, 10);
}

camera* create_camera(
	uint32_t width,
	uint32_t height)
{
	char filename[sizeof(temp_name) + 23] = "/tmp/lego-sort-XXXXXX";

	size_t buflen = 22 + 2 * MAX_UINT32_OUTPUT_SIZE 
		+ sizeof(command_template);

	// Allocate memory for all buffers up front
	camera* cam = malloc(sizeof(camera) + strlen(filename) + 1);
	char* command = malloc(buflen);
	char* tmpdir = (char*)(cam + 1);

	if (!cam || !command)
	{
		free(cam);
		free(command);
		return NULL;
	}

	cam->width = width;
	cam->height = height;
	
	// Create a temporary directory to store the output
	mkdtemp(filename);
	cam->tmpdir = strcpy(tmpdir, filename);

	snprintf(
		command,
		buflen, 
		command_template,
		width, 
		height, 
		strcat(filename, temp_name));

	cam->stream = popen(command, "r");

	// Not entirely sure what to do if 
	// command creation fails
	assert(cam->stream);
	free(command);

	cam->pid = get_pid("raspistill");

	// Take the first picture so that there
	// is something there when take_picture
	// is called for the first time.
	
	// Sleep for 1s so that raspistill can initialize 
	usleep(1000000);

	// Send signal so raspistill outputs an image
	kill(cam->pid, SIGUSR1);

	return cam;
}
void destroy_camera(camera* cam)
{
	char cmdbuf[64] = "rm -rf ";
	if (!cam)
		return;

	pclose(cam->stream);

	// Kill raspistill (politely)
	kill(cam->pid, SIGTERM);

	// Sleep for 0.5 seconds
	usleep(500000);

	// Remove temporary directory
	strcat(cmdbuf, cam->tmpdir);
	system(cmdbuf);

	// Note: We don't free tmpdir since
	//       this frees its buffer as well
	free(cam);
}

camera_error_code take_picture(
	camera* cam,
	image* out)
{
	char buffer[sizeof(temp_name) + 64];

	if (!cam || !out)
		return CAMERA_ERR_INVALID_ARGUMENTS;

	strcat(strcpy(buffer, cam->tmpdir), temp_name);

	int ret = import_image(buffer, out);

	if (ret == 1)
		return CAMERA_ERR_OUT_OF_MEMORY;
	else if (ret != 0)
		return CAMERA_ERR_INTERNAL_ERROR;

	// Send signal to raspistill to take another picture
	kill(cam->pid, SIGUSR1);

	return CAMERA_ERR_SUCCESS;
}

