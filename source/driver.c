#include <stdio.h>

#include "block_detector.h"
#include "block_recognizer.h"
#include "colour_detector.h"
#include "image.h"
#include "pngimport.h"
#include "set_management.h"

// this is the driver which is to be run over and over again until the list is full or we stop

int main (void)
{
	set myset = set_management();
	bool blocks_are_left = true;
	while(blocks_are_left)
	{
		// Should load the given image off of disk
		image source_img;
		int err = import_image(argv[1], &source_img);
		
		if(block_in_image(source_img))
		{
			block_type type = recognize_block(gray);
			lego_colour colour = detect_colour(img);
			for(int i = 0; i < myset.size; i++)
			{
				if(myset.array[i].blocks_left > 0)
				{
					if(myset.array[i].length == type.length && myset.array[i].width == type.width
						&& myset.array[i].thickness == type.thickness && myset.array[i].colour == colour.lego_id)
					{
						inSet(1)//turn green light on
						// wait 3 seconds???
						myset.array[i].blocks_left --;
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


