#ifndef MANDELBROT
#define MANDELBROT

#include "common.h"

//! @details Calculates for all points in specified area (see below) 
//! number of steps it takes the point to enter the 'DEAD ZONE' (see .h).
//! If ret_res != NULL, calls this func for every calculated point, using
//! its integer indexes (like in a bidimensional arrey) and passing the number 
//! of step, on which the point entered the 'DEAD ZONE'. If it is larger than
//! uint8_t max value, returns zero (which can mean it is actually infinity).
//! Area:
//!     - (top_left_x, top_left_y) is its top left corner in cartesian coordinates; 
//!     - area's width  = image_width*step;
//!     - area's height = image_height*step;
//!     - total number of procesed points = image_width*image_height.
//! Step:
//!     - distance between two consecutive points 
void calculate_image( unsigned image_width, unsigned image_height, 
                      double top_left_x, double top_left_y, double step,
                      void (*ret_res)(unsigned i,unsigned j,u_int8_t step_number) = NULL );

#endif /* MANDELBROT */