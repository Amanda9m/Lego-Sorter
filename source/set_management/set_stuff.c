#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "block_detector.h"
#include "block_recognizer.h"
#include "colour_detector.h"
#include "pngimport.h" 
#include "set_management.h" 

// gets input from user_input
/*
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
} set; */

set set_management (void)
{ 
	FILE *input;

	input = fopen("user_input", "r");

	if (!input)
	{
		printf("User input not found!\n");
		assert(input);
	}

	int num = 0;
	// ./a.out < user_input.txt;
	fscanf(input, "%d", &num);

	blocks * array = malloc (num * sizeof(blocks));

	for(int i = 0; i < num; i ++)
	{
		fscanf(input, "%d, %d, %d, %d, %d", &array[i].length, &array[i].width, &array[i].thickness, &array[i].colour, &array[i].blocks_left);
		/*array[i].length = size[0] - 48;
		array[i].width = size[3] -48;
		array[i].thickness = size[6] -48;
		array[i].colour = size[9] -48;
		array[i].blocks_left = size[12] -48; */
	}

	set myset;
	myset.size = num;
	myset.array = array;
	return (myset);
}