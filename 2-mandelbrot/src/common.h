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

const u_int8_t INFINITE_STEP_NUMBER = __UINT8_MAX__ - 1;

//! @brief Everything not in the circle of this radius centered at 
//! coordinate system's origin is considered the 'DEAD ZONE'.
const double DEATH_RADIUS = 10.0; 

const double ZOOM_MUL = 1.01;
const double SPEED_MUL = 5;

const sf::Keyboard::Key KEY_MOVE_UP     = sf::Keyboard::W;
const sf::Keyboard::Key KEY_MOVE_LEFT   = sf::Keyboard::A;
const sf::Keyboard::Key KEY_MOVE_RIGHT  = sf::Keyboard::D;
const sf::Keyboard::Key KEY_MOVE_DOWN   = sf::Keyboard::S;
const sf::Keyboard::Key KEY_ZOOM_IN     = sf::Keyboard::Q;
const sf::Keyboard::Key KEY_ZOOM_OUT    = sf::Keyboard::E;
const sf::Keyboard::Key KEY_SPEED       = sf::Keyboard::LShift;
const sf::Keyboard::Key KEY_PRINT_CNTR  = sf::Keyboard::C;
const sf::Keyboard::Key KEY_PRINT_MOUSE = sf::Keyboard::M;
const sf::Keyboard::Key KEY_GOTO_ORIG   = sf::Keyboard::O;

struct State
{
    const unsigned window_width   = W_WIDTH;
    const unsigned window_height  = W_HEIGHT;
    double top_left_x       = DEFAULT_TOP_LEFT_X;
    double top_left_y       = DEFAULT_TOP_LEFT_Y;
    double step             = DEFAULT_STEP;
};

#endif /* MANDELBROT_COMMON_H */