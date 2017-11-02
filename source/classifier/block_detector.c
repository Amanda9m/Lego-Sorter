
#include "opencv-sobel.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Accesses a pixel element at (x, y) and gives the channel component
#define img_pixel_at(src, x, y, channel) ((src).img[(y) * (src).width * (src).channels + (x) * (src).channels + (channel)])


#define edge_threshold 128
#define num_edge_threshhold 0
#define near_edge_threshhold 2

typedef struct
{
	size_t x, y;
} point;

typedef struct
{
	size_t start;
	size_t end;
	size_t size;
	size_t sz_check;
	point* mem;
} queue;

queue make_queue(size_t size)
{
	queue q;

	q.size = size;
	q.sz_check = 0;
	q.start = 0;
	q.end = 0;
	q.mem = malloc(sizeof(point) * q.size);

	return q;
}
point make_point(size_t x, size_t y)
{
	point p = { x, y };
	return p;
}

void queue_enqueue(queue* q, point pt)
{
	assert(q != NULL);

	q->mem[q->end] = pt;

	q->end++;
	q->sz_check++;

	assert(q->sz_check < q->size);

	if (q->end >= q->size)
		q->end -= q->size;
}
point queue_dequeue(queue* q)
{
	assert(q != NULL);
	assert(q->end != q->start);
		
	point pt = q->mem[q->start];
	q->start++;
	q->sz_check--;

	if (q->start >= q->size)
		q->start -= q->size;

	return pt;
}
bool queue_empty(queue* q)
{
	return q->end == q->start;
}

int give_mask(image source, image* mask)
{
	// Make sure that the source has a size
	assert(source.width != 0 && source.height != 0);
	// Make sure that the source image is greyscale
	assert(source.channels == 1);
	// Make sure that mask isn't null
	assert(mask != NULL);

	mask->height = source.height;
	mask->width = source.width;
	mask->channels = 1;
	// calloc automatically allocates zeroed memory
	mask->img = calloc(1, sizeof(point) * source.height * source.width);

	if (!mask->img)
		return -1;

	queue q = make_queue(source.height * source.width * 4);
	if (!q.mem)
		return -1;

	queue_enqueue(&q, make_point(0, 0));

	while (!queue_empty(&q))
	{
		point pt = queue_dequeue(&q);

		if (img_pixel_at(*mask, pt.x, pt.y, 0) != 0)
			continue;
		img_pixel_at(*mask, pt.x, pt.y, 0) = 255;

		if (pt.x > 0)
		{
			// Set pixel above if above is not an edge
			if (pt.y > 0 && img_pixel_at(*mask, pt.x - 1, pt.y - 1, 0) == 0
				&& img_pixel_at(source, pt.x - 1, pt.y - 1, 0) >= edge_threshold)
			{
				queue_enqueue(&q, make_point(pt.x - 1, pt.y - 1));
			}
			if (pt.y < source.height - 1 && img_pixel_at(*mask, pt.x - 1, pt.y + 1, 0) == 0
				&& img_pixel_at(source, pt.x - 1, pt.y + 1, 0) >= edge_threshold)
			{
				queue_enqueue(&q, make_point(pt.x - 1, pt.y + 1));
			}
		}
		if (pt.x < source.width - 1)
		{
			if (pt.y > 0 && img_pixel_at(*mask, pt.x + 1, pt.y - 1, 0) == 0
				&& img_pixel_at(source, pt.x + 1, pt.y - 1, 0) >= edge_threshold)
			{
				queue_enqueue(&q, make_point(pt.x + 1, pt.y - 1));
			}
			if (pt.y < source.height - 1 && img_pixel_at(*mask, pt.x + 1, pt.y + 1, 0) == 0
				&& img_pixel_at(source, pt.x + 1, pt.y + 1, 0) >= edge_threshold)
			{
				queue_enqueue(&q, make_point(pt.x + 1, pt.y + 1));
			}
		}
	}

	return 0;
}

bool is_block(image source, image* block_mask)
{
	/* Input checks */
	// Source image must have a size
	assert(source.width != 0 && source.height != 0);
	// Source image must be greyscale
	assert(source.channels == 1);
	// For now, block_mask may not be null
	assert(block_mask != NULL);

	image mask;
	int areEdges = 0;

	sobel_filter_error_code err = sobel_filter(source, &mask);
	// Really really hope that the filter succeeds
	assert(err == SOBEL_FILTER_SUCCESS);

	//Thickening edges
	for (size_t i = 1; i < (mask.width -1); i++)
	{
		for (size_t j = 1; j < (mask.height - 1); j++)
		{
			if (img_pixel_at(mask, i, j, 1) >= edge_threshold)
			{
				for (int p = -2; p < 3; p++)
				{
					for (int q = -2; q < 3; q++)
					{
						if ((i + p) > 0 && (i + p) < mask.width && (j + q) > 0 && (j + q) < mask.height)
							img_pixel_at(mask, i + p, j + q, 0) = edge_threshold;
						// else // The edge is very near the edge of the image, ie it is probably not wholly inclosed
							// return false;
					}
				}
			}
		}
	}
	err = give_mask(source, block_mask);
	assert(err == 0);
	mask = *block_mask;
	// check that there is a block within the image
	int is_over_threshold = 0;
	for (size_t i = 0; i < mask.width; i++)
	{
		for (size_t j = 0; j < mask.height; j++)
		{
			if (img_pixel_at(mask, i, j, 1) < edge_threshold) // If that pixel is dark (ie is within the block)
			{
				is_over_threshold++;
				if ((i < near_edge_threshhold) || ((mask.width - i) < near_edge_threshhold) || (j < near_edge_threshhold) || ((mask.height - j) < near_edge_threshhold)) //if the block is near/touching the edge
					return false;
			}
		}
	}
	if (is_over_threshold > num_edge_threshhold) // If there is a block in the picture that is significantly large
		return true;
	else
		return false;
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

	// TEMPORARY: Make block_mask an empty image
	// This should make any function that is then
	// called with block_mask assert because it
	// isn't a valid image.
	block_mask->height = 0;
	block_mask->width = 0;
	block_mask->channels = 0;
	block_mask->img = NULL;

	return is_block(source, block_mask);
}
