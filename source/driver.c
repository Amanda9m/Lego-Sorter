#include <stdio.h>
#include <python2.7/Python.h>

#include "block_detector.h"
#include "block_recognizer.h"
#include "colour_detector.h"
#include "image.h"
#include "pngimport.h"
#include "set_management.h"
#include "LED.py"

// this is the driver which is to be run over and over again until the list is full or we stop

int main (void)
{
	array = set_management(user_input_document); //this is not at all how i call this and i'm not sure i'll get it, need to work on getting this array.
	bool blocks_are_left = true;
	while(blocks_are_left)
	{
		// Should load the given image off of disk
		image source_img;
		int err = import_image(argv[1], &source_img);
		
		if(block_in_image(source_img))
		{
			block_type type = recognize_block(gray);
			lego_colour colour = detect_colour(img); //make this mean colour id as in my look up table or change my lookup table to right ids
			for(int i = 0; i < n; i++) //need to get n from array, need to output that from function too oopssssss MAKE THAT HAPPEN
			{
				if(array[i].blocks_left > 0)
				{
					if(array[i].length == type.length && array[i].width == type.width
						&& array[i].thickness == type.thickness && array[i].colour == colour)
					{
						inSet(1)//turn green light on
						// wait 3 seconds???
						array[i].blocks_left --;
						i = n;
					}
				}
			}
		}
	}
}


//input user files

//call tensorflow block detect

//if yes, continue, if no, try again

//call tensorflow block type and color type

//compare tensorflow block type and user input, color and user input

//if yes, green light, if no, red


