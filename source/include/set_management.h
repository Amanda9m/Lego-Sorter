#ifndef SET_MANAGEMENT_H
#define SET_MANAGEMENT_H

#include <stdbool.h>

#include "image.h"

typedef struct
{
	int length;
	int width;
	int thickness;
	int colour;
	int blocks_left;
}blocks;

int main (void);

#endif
