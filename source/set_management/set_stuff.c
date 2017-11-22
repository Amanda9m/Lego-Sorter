#include <stdio.h>
#include <stdlib.h>

#include "block_detector.h"
#include "block_recognizer.h"
#include "colour_detector.h"
#include "pngimport.h" 
#include "set_management.h"

// gets input from user_input

set main (void)
{ 
	char number_of_types[3];
	int num = 0;
	// ./a.out < user_input.txt;
	fgets(number_of_types, 3, stdin);
	num = number_of_types[0] - 48; // To convert from ascii code to numeric value
	blocks * array = malloc (num * sizeof(blocks));
	char block_enter[15];
	array[3].length = 1;

	for(int i = 0; i < num; i ++)
	{
		fgets(block_enter, 15, stdin);
		array[i].length = block_enter[0] - 48;
		array[i].width = block_enter[3] -48;
		array[i].thickness = block_enter[6] -48;
		array[i].colour = block_enter[9] -48;
		array[i].blocks_left = block_enter[12] -48;
	}

	set myset;
	myset.size = num;
	myset.array = array;
	return (myset);
}