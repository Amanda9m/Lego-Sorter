#ifndef SET_MANAGEMENT_H
#define SET_MANAGEMENT_H

#include "image.h"
#include <stdbool.h>

//The struct which returns the various properties of a block


typedef struct
{
	int length;
	int width;
	int thickness;
	int colour;
	int blocks_left;
}blocks;

//the return struct from the main function, returning the size of the array, and the array itself (which is an array of block types)
typedef struct{
    int size;
    blocks * array; //call the array by calling (for instance) myset.array[i].length
} set;

set set_management(); //input: nothing, output: struct set, including array and its size

#endif
