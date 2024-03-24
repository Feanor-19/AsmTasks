#include "mandelbrot.h"
#include <math.h>

void calculate_image( unsigned image_width, unsigned image_height, 
                      double top_left_x, double top_left_y, double step,
                      void (*ret_res)(unsigned i,unsigned j,u_int8_t step_number) )
{
    for ( unsigned i = 0; i < image_height; i++ )
    {
        for ( unsigned j = 0; j < image_width; j++ )
        {
            double curr_x = top_left_x + j*step;
            double curr_y = top_left_y - i*step; //< axis 'i' points down


            //TODO - TEST!!!
            ret_res( i, j, curr_x*curr_x + curr_y*curr_y <= 4.0 ? 128 : 0 );
        }
    }
}