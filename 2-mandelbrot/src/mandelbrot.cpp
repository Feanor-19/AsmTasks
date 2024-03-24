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
            double curr_y = top_left_y + i*step;


            //TODO - TEST!!!
            ret_res( i, j, pow(sin( curr_x ), 2) + pow(sin( curr_y ), 2) <= 1.0 ? 128 : 0 );
        }
    }
}