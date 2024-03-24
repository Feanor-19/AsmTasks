#include "common.h"
#include "graphics.h"
#include "mandelbrot.h"

void handle_events( sf::Window &window );


int main(  )
{
    sf::RenderWindow window(sf::VideoMode( W_WIDTH, W_HEIGHT ), W_NAME, 
                            sf::Style::Titlebar | sf::Style::Close);

    // drawing initial image
    init_image( W_WIDTH, W_HEIGHT );
    calculate_image( W_WIDTH, W_HEIGHT, DEFAULT_TOP_LEFT_X, DEFAULT_TOP_LEFT_Y, DEFAULT_STEP, set_pixel_color );

    sf::Texture window_texture;
    window_texture.loadFromImage( get_image() );

    sf::Sprite window_sprite;
    window_sprite.setTexture( window_texture );

    // main loop
    while (window.isOpen())
    {
        handle_events(window);

        // no window.clear(), because sprite takes up the whole window
        // and is always opaque

        window.draw( window_sprite );

        window.display();
    }
    
}

void handle_events( sf::Window &window )
{
    sf::Event event = {};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}