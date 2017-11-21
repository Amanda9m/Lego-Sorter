#include <stdio.h>

#include "block_detector.h"
#include "block_recognizer.h"
#include "colour_detector.h"
#include "pngimport.h"
#include "set_management.h"

// get's input from user_input_document

struct * main (void)
{
	char number_of_types[3];
	int num = 0;
	// ./a.out < user_input_document;
	fgets(number_of_types, 3, stdin);
	num = number_of_types[0] - 48; // To convert from ascii code to numeric value
	blocks array[num];
	char block_enter[15];

	for(int i = 0; i < num; i ++)
	{
		fgets(block_enter, 15, stdin);
		array[i].length = block_enter[0] - 48;
		array[i].width = block_enter[3] -48;
		array[i].thickness = block_enter[6] -48;
		array[i].colour = block_enter[9] -48;
		array[i].blocks_left = block_enter[12] -48;
	}
	
	//block_type type = recognize_block(img);
	//lego_colour colour = detect_colour(img);

	return array[0];
}