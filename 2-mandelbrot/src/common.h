#ifndef MANDELBROT_COMMON_H
#define MANDELBROT_COMMON_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const unsigned    W_HEIGHT = 600;
const unsigned    W_WIDTH  = 800;
const char* const W_NAME   = "Mandelbrot!"; 

const double DEFAULT_TOP_LEFT_X = -2.0;
const double DEFAULT_TOP_LEFT_Y = 1.5;
const double DEFAULT_STEP       = 2.0 / (W_WIDTH / 2);


#endif /* MANDELBROT_COMMON_H */