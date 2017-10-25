// Code to detect if a block exists fully within the picture


#include "opencv-sobel.h"

#include <stdbool.h>
#include <assert.h>
#include <define.h>
// Accesses a pixel element at (x, y) and gives the channel component
#define img_pixel_at(src, x, y, channel) ((src).img[y * (src).width * (src).channels + x * (src).channels + channel])


#define edge_threshold 128 // Darker is smaller
#define num_edge_threshhold 400

bool is_block(image source, image* block_mask)
{
    int is_block = 0;
    image mask = sobel_filter(source);
    int areEdges = 0;
    //Thickening edges
    for(int i = 0; i < mask.width; i++)
    {
        for(int j = 0; j < mask.height; j++)
        {
            if (img_pixel_at(mask, i, j, 1) >= edge_threshold)
            {
                for(int p = -1; p < 2; p++)
                {
                    for(int q = -1; q <2; q++)
                    {
                        if((i+p) > 0 && (i+p) < mask.width && (j+q) > 0 && (j+q) < mask.height)
                            img_pixel_at(mask, i+p, j+q, 1) = edge_threshold;
                        else // The edge is very near the edge of the image, ie it is probably not wholly inclosed
                            return false;
                    }
                }
            }
        }
    }
    mask = give_mask(mask);
    // check that there is a block within the image
    int is_over_threshold = 0;
    for(int i = 0; i < mask.width; i++)
    {
        for(int j = 0; j < mask.height; j++)
        {
            if(img_pixel_at(mask, i, j, 1) < edge_threshold) // If that pixel is dark (ie is within the block)
                is_over_threshold++;
        }
    }
    if(is_over_threshold > num_edge_threshhold) // If there is a block in the picture that is significantly large
        return true;
    else
        return false;
}  

image give_mask (image source)
{
    // Filling in mask
    for(int i = 0; i < source.width; i++)
    {
        //Filling in from left side until it hits an edge
        for(int j = 0; img_pixel_at(source, i, j, 1) < edge_threshold; j++)
        {
            img_pixel_at(source, i, j, 1) = edge_threshold;
        }
        //filling in from right side until it hits an edge
        for(int j = source.height; img_pixel_at(source, i, j, 1) < edge_threshold; j--)
        {
            img_pixel_at(source, i, j, 1) = edge_threshold;
        }
    }
    //if it is a full block, there will be multiple rows of black, if not, the image will be almost entirely white
}
