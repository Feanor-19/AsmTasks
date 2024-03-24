#ifndef MANDELBROT_GRAPHICS
#define MANDELBROT_GRAPHICS

#include "common.h"

//! @brief Call this before any other calls concerning the IMAGE.
void init_image( unsigned width, unsigned height, sf::Color filling_color = sf::Color::Black );

//! @brief Sets pixel as in bidimensional array IMAGE[i][j] with color,
//! which depeneds on the step_number.
void set_pixel_color( unsigned i, unsigned j, u_int8_t step_number );

//! @brief Get const IMAGE reference.
const sf::Image& get_image();

#endif /* MANDELBROT_GRAPHICS */