
extern "C" {
#include "image.h"
#include "opencv-sobel.h"
}

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core.hpp"

#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstring>

// Accesses a pixel element at (x, y) and gives the channel component
#define img_pixel_at(src, x, y, channel) ((src).img[y * (src).width * (src).channels + x * (src).channels + channel])


#define edge_threshold 128
#define num_edge_threshhold 400;

bool is_block(image source, image* block_mask)
{
    int is_block = 0;
    source = sobel_filter(source);
    int areEdges = 0;
    //Thickening edges
    for(int i = 0; i < source.width; i++)
    {
        for(int j = 0; j < source.height; j++)
        {
            if (img_pixel(source, i, j) >= edge_threshold)
            {
                for(int p = -1; p < 2; p++)
                {
                    for(int q = -1; q <2; q++)
                    {
                        if((i+p) > 0 && (i+p) < source.width && (j+q) > 0 && (j+q) < source.length)
                            img_pixel(source, i+p, j+q) == edge_threshhold;
                        else // The edge is very near the edge of the image, ie it is probably not wholly inclosed
                            return 0;
                    }
                }
            }
        }
    }
    // Filling in mask
    for(int i = 0; i < source.width; i++)
    {
        for(int j = 0; i< source.length)
}
