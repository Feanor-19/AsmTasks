#include "common.h"
#include "handlers.h"
#include "image.h"
#include "mandelbrot.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode( W_WIDTH, W_HEIGHT ), W_NAME, 
                            sf::Style::Titlebar | sf::Style::Close);
    State state;

    // drawing initial image
    init_image( state.window_width, state.window_height );
    calculate_image( state.window_width, state.window_height, state.top_left_x, 
                     state.top_left_y, state.step, set_pixel_color );

    sf::Texture window_texture;
    window_texture.loadFromImage( get_image() );

    sf::Sprite window_sprite;
    window_sprite.setTexture( window_texture );

    // main loop
    while (window.isOpen())
    {
        handle_events(window);

        if ( handle_keyboard( &state ) )
        {
            init_image( state.window_width, state.window_height );
            calculate_image( state.window_width, state.window_height, state.top_left_x, 
                             state.top_left_y, state.step, set_pixel_color );
            window_texture.update( get_image() );
        }

        // no window.clear(), because sprite takes up the whole window
        // and is always opaque

        window.draw( window_sprite );
        window.display();
    }
    
}