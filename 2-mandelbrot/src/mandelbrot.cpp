#include "mandelbrot.h"

//! @brief Calculates at which step number given point (start_x, start_y)
//! enters dead zone. 
inline u_int8_t calc_step_number( double start_x, double start_y )
{
    double curr_x = 0;
    double curr_y = 0;

    u_int8_t step_number = 0;
    for ( ; step_number < INFINITE_STEP_NUMBER; step_number++ )
    {
        if (curr_x*curr_x + curr_y*curr_y >= DEATH_RADIUS * DEATH_RADIUS)
            break;

        double new_curr_x = curr_x*curr_x - curr_y*curr_y + start_x;
        double new_curr_y = 2*curr_x*curr_y + start_y;

        curr_x = new_curr_x;
        curr_y = new_curr_y;
    }

    return step_number;
}

void calculate_image( unsigned image_width, unsigned image_height, 
                      double top_left_x, double top_left_y, double step,
                      void (*ret_res)(unsigned i,unsigned j,u_int8_t step_number) )
{
    for ( unsigned i = 0; i < image_height; i++ )
    {
        for ( unsigned j = 0; j < image_width; j++ )
        {
            double start_x = top_left_x + j*step;
            double start_y = top_left_y - i*step; //< axis 'i' points down

            ret_res( i, j, calc_step_number( start_x, start_y ) );
        }
    }
}