
#include "opencv-sobel.h"

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Accesses a pixel element at (x, y) and gives the channel component
#define img_pixel_at(src, x, y, channel) ((src).img[(y) * (src).width * (src).channels + (x) * (src).channels + (channel)])


#define edge_threshold 128
#define num_edge_threshold 0
#define near_edge_threshold 2

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

int calc_mask(image source, image* mask)
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

	for (size_t y = 0; y < source.height; ++y)
	{
		for (size_t x = 0; x < source.width; ++x)
		{
			if (img_pixel_at(source, x, y, 1) >= edge_threshold)
				img_pixel_at(*mask, x, y, 1) = 255;
		}
	}

	return 0;
}
int thicken_edges(image mask, image* out_mask)
{
	assert(mask.channels == 1);
	assert(mask.height != 0 && mask.width != 0);
	assert(mask.img != NULL);
	assert(out_mask != NULL);

	out_mask->channels = 1;
	out_mask->height = mask.height;
	out_mask->width = mask.width;
	out_mask->img = calloc(1, sizeof(uint8_t) * mask.width * mask.height);

	if (!out_mask->img)
		return 1;

	for (size_t y = 1; y < mask.height - 1; ++y)
	{
		for (size_t x = 1; x < mask.width - 1; ++x)
		{
			if (img_pixel_at(mask, x, y, 1) >= edge_threshold)
			{
				img_pixel_at(*out_mask, x - 1, y - 1, 1) = UINT8_MAX;
				img_pixel_at(*out_mask, x - 1, y, 1) = UINT8_MAX;
				img_pixel_at(*out_mask, x - 1, y + 1, 1) = UINT8_MAX;

				img_pixel_at(*out_mask, x, y - 1, 1) = UINT8_MAX;
				img_pixel_at(*out_mask, x, y, 1) = UINT8_MAX;
				img_pixel_at(*out_mask, x, y + 1, 1) = UINT8_MAX;

				img_pixel_at(*out_mask, x + 1, y - 1, 1) = UINT8_MAX;
				img_pixel_at(*out_mask, x + 1, y, 1) = UINT8_MAX;
				img_pixel_at(*out_mask, x + 1, y + 1, 1) = UINT8_MAX;
			}
		}
	}

	return 0;
}
bool block_near_edge(image mask)
{
	assert(mask.channels == 1);
	assert(mask.height != 0 && mask.width != 0);
	assert(mask.img);

	// Loop over top of image
	for (uint32_t y = 0; y < near_edge_threshold; ++y)
	{
		for (uint32_t x = 0; x < mask.width; ++x)
		{
			if (img_pixel_at(mask, x, y, 1) < edge_threshold)
				return true;
		}
	}

	// Loop over middle of image
	for (uint32_t y = near_edge_threshold; y < mask.height - near_edge_threshold; ++y)
	{
		for (uint32_t x = 0; x < near_edge_threshold; ++x)
		{
			if (img_pixel_at(mask, x, y, 1) >= edge_threshold)
				return true;
		}

		for (uint32_t x = mask.width - near_edge_threshold; x < mask.width; ++x)
		{
			if (img_pixel_at(mask, x, y, 1) >= edge_threshold)
				return true;
		}
	}

	// Loop over bottom of image
	for (uint32_t y = mask.height - near_edge_threshold; y < mask.height; ++y)
	{
		for (uint32_t x = 0; x < mask.width; ++x)
		{
			if (img_pixel_at(mask, x, y, 1) >= edge_threshold)
				return true;
		}
	}

	return false;
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

	image sobel, edges;
	int areEdges = 0;

	if (sobel_filter(source, &sobel) != SOBEL_FILTER_SUCCESS)
		// Optionally could return an error code here
		// would have to clean up memory though
		assert(false);

	//Thickening edges
	if (thicken_edges(sobel, &edges) != 0)
		// Optionally could return an error code here
		// would have to clean up memory though
		assert(false);

	if (calc_mask(edges, block_mask) != 0)
		// Optionally could return an error code here
		// would have to clean up memory though
		assert(false);

	free(sobel.img);
	free(edges.img);

	if (block_near_edge(*block_mask))
	{
		free(block_mask->img);
		return false;
	}

	return true;
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
