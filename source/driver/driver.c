#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "block_detector.h"
#include "block_recognizer.h"
#include "colour_detector.h"
#include "image.h"
#include "pngimport.h"
#include "set_management.h"
#include "camera.h"


// this is the driver which is to be run over and over again until the list is full or we stop

void inSet(int v)
{
	char command[100];
	
	snprintf(command, sizeof(command),
		"python LED.py %d", v);

	system(command);
}

int main (int argc, char** argv)
{
	set myset = set_management();
	camera* cam = create_camera(224, 224);
	printf("Camera done\n");
	bool blocks_are_left = true;
	while(blocks_are_left)
	{
		// Should load the given image off of disk
		image source_img;
		take_picture(cam, &source_img);
		//printf("took picture\n");

		if (source_img.height == 0 || source_img.width == 0)
			continue;

        image img2 = resize_image(source_img, 224, 224);
        image gray = grayscaled_image(img2);
		
		if(block_in_image(img2));
		{
			fprintf(stderr, "Found Block\n");
            
			block_type type = recognize_block(gray);
			lego_colour colour = detect_colour(img2);
			for(int i = 0; i < myset.size; i++)
			{
				if(myset.array[i].blocks_left > 0)
				{
					if(myset.array[i].length == type.length
						&& myset.array[i].width == type.width
						&& myset.array[i].thickness == type.thickness
						&& myset.array[i].colour == colour.lego_id)
					{
						inSet(1);//turn blue light on
						// wait 3 seconds???
						myset.array[i].blocks_left --;
						i = myset.size;
						printf("Block in set!\n");
					}
				}
			}

			printf("Block Type: %dx%dx%d\nBlock Colour: %s\n",
				type.width, type.length, type.thickness,
				colour.colour_name);
		}

		free(img2.img);
		free(gray.img);
		free(source_img.img);
		source_img.height = 0;
		source_img.img = NULL;
	}

	destroy_camera(cam);
}


//input user files

//call tensorflow block detect

//if yes, continue, if no, try again

//call tensorflow block type and color type

//compare tensorflow block type and user input, color and user input

//if yes, green light, if no, red


