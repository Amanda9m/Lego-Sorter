
#include "opencv-sobel.h"

#include <stdbool.h>
#include <assert.h>

// Accesses a pixel element at (x, y) and gives the channel component
#define img_pixel_at(src, x, y, channel) ((src).img[y * (src).width * (src).channels + x * (src).channels + channel])


#define edge_threshold 128
#define num_edge_threshhold 400;

bool is_block(image source, image* block_mask)
{
	/*
	I've commented this out since it seems
	to have been deleted from the source tree.
	In addition, it doesn't compile since it
	doesn't appear to use a few methods correctly
	and I'm not sure what was intended.

	int is_block = 0;
	source = sobel_filter(source);
	int areEdges = 0;
	//Thickening edges
	for (int i = 0; i < source.width; i++)
	{
		for (int j = 0; j < source.height; j++)
		{
			if (img_pixel_at(source, i, j, 0) >= edge_threshold)
			{
				for (int p = -1; p < 2; p++)
				{
					for (int q = -1; q < 2; q++)
					{
						if ((i + p) > 0 && (i + p) < source.width && (j + q) > 0 && (j + q) < source.height)
							img_pixel_at(source, i + p, j + q, 0) == edge_threshhold;
						else // The edge is very near the edge of the image, ie it is probably not wholly inclosed
							return 0;
					}
				}
			}
		}
	}
	// Filling in mask
	for (int i = 0; i < source.width; i++)
	{
		for (int j = 0; j < source.height; j++)
		{

		}
	}
	*/
}

// Method stub for block_in_image
bool block_in_image(image source, image* block_mask)
{
	// It doesn't really make sense to check if there is 
	// a block in an empty image. Just returning false 
	// is an option, but for now this method will just
	// assert to ensure that the image isn't empty.
	assert(source.height != 0 && source.height != 0);

	// block_in_image requires that the image be greyscale
	assert(source.channels == 1);

	// Require that the source image be a valid image.
	assert(source.img != NULL);

	// TODO: Actually implement the method
	return true;
}
