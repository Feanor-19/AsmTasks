#include "handlers.h"

void handle_events( sf::Window &window )
{
    sf::Event event = {};
    while (window.pollEvent(event))
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
#pragma GCC diagnostic pop
    }
}

bool handle_keyboard( State *state_ptr )
{
    bool changes = false;

    if ( sf::Keyboard::isKeyPressed( KEY_MOVE_UP ) )
    {
        state_ptr->top_left_y += state_ptr->step;
        
        changes = true;
    }

    if ( sf::Keyboard::isKeyPressed( KEY_MOVE_DOWN ) )
    {
        state_ptr->top_left_y -= state_ptr->step;
        
        changes = true;
    }

    if ( sf::Keyboard::isKeyPressed( KEY_MOVE_LEFT ) )
    {
        state_ptr->top_left_x -= state_ptr->step;
        
        changes = true;
    }

    if ( sf::Keyboard::isKeyPressed( KEY_MOVE_RIGHT ) )
    {
        state_ptr->top_left_x += state_ptr->step;
        
        changes = true;
    }

    if ( sf::Keyboard::isKeyPressed( KEY_ZOOM_IN ) )
    {
        double old_step = state_ptr->step; 
        double new_step = old_step / ZOOM_MUL;

        state_ptr->step = new_step;
        state_ptr->top_left_x += ( old_step - new_step ) / 2.0 * state_ptr->window_width;
        state_ptr->top_left_y -= ( old_step - new_step ) / 2.0 * state_ptr->window_height;
        
        changes = true;
    }

    if ( sf::Keyboard::isKeyPressed( KEY_ZOOM_OUT ) )
    {
        double old_step = state_ptr->step; 
        double new_step = old_step * ZOOM_MUL;

        state_ptr->step = new_step;
        state_ptr->top_left_x -= ( new_step - old_step ) / 2.0 * state_ptr->window_width;
        state_ptr->top_left_y += ( new_step - old_step ) / 2.0 * state_ptr->window_height;
 
        changes = true;
    }

    return changes;
}