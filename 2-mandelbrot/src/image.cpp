#include "image.h"
#include <assert.h>

//! @brief Current image to be drawn.
//! @attention CALL init_image() BEFORE CALLING EVERYTHING ELSE!
//! @details Changed by calling set_pixel_color() and retrived by get_image()
static sf::Image IMAGE       = sf::Image();
static unsigned IMAGE_WIDTH  = 0;
static unsigned IMAGE_HEIGHT = 0;

void init_image( unsigned width, unsigned height, sf::Color filling_color )
{
    IMAGE_WIDTH  = width;
    IMAGE_HEIGHT = height;
    IMAGE.create( width, height, filling_color );
}

inline sf::Color step_number_to_color( u_int8_t step_number )
{
    if (step_number == 0)
        return sf::Color::Black;

    return sf::Color(255 - step_number,
                     (step_number % 2)*64,
                     step_number );
}

void set_pixel_color( unsigned i, unsigned j, u_int8_t step_number )
{
    assert( i < IMAGE_HEIGHT );
    assert( j < IMAGE_WIDTH );

    IMAGE.setPixel( j, i, step_number_to_color( step_number ) );
}

const sf::Image& get_image()
{
    assert( IMAGE_WIDTH && IMAGE_HEIGHT );

    return IMAGE;
}