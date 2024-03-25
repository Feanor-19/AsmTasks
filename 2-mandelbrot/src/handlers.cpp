#include "handlers.h"

void handle_events( sf::Window &window, const State *state_ptr )
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
        case sf::Event::KeyPressed:
            if (event.key.code == KEY_PRINT_CNTR)
            {
                double cntr_x = state_ptr->top_left_x + state_ptr->step * (state_ptr->window_width) / 2;
                double cntr_y = state_ptr->top_left_y - state_ptr->step * (state_ptr->window_height) / 2;
                printf( "Current coordinate of the view's center: % -15e % -15e\n", cntr_x, cntr_y);
            } 

            if (event.key.code == KEY_PRINT_MOUSE)
            {
                int mouse_x = sf::Mouse::getPosition(window).x;
                int mouse_y = sf::Mouse::getPosition(window).y;

                double coord_x = state_ptr->top_left_x + state_ptr->step * mouse_x;
                double coord_y = state_ptr->top_left_y - state_ptr->step * mouse_y;
                printf( "Current coordinate under the mouse pointer: % -15e % -15e\n", coord_x, coord_y);
            } 
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

    //REVIEW - как лучше организовать? что насчет return true в каждом if?

    double speed_mul = 1.0;
    if ( sf::Keyboard::isKeyPressed( KEY_SPEED ) )
        speed_mul = SPEED_MUL;

    if ( sf::Keyboard::isKeyPressed( KEY_MOVE_UP ) )
    {
        state_ptr->top_left_y += state_ptr->step * speed_mul;
        
        changes = true;
    }

    if ( sf::Keyboard::isKeyPressed( KEY_MOVE_DOWN ) )
    {
        state_ptr->top_left_y -= state_ptr->step * speed_mul;
        
        changes = true;
    }

    if ( sf::Keyboard::isKeyPressed( KEY_MOVE_LEFT ) )
    {
        state_ptr->top_left_x -= state_ptr->step * speed_mul;
        
        changes = true;
    }

    if ( sf::Keyboard::isKeyPressed( KEY_MOVE_RIGHT ) )
    {
        state_ptr->top_left_x += state_ptr->step * speed_mul;
        
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

    if ( sf::Keyboard::isKeyPressed( KEY_GOTO_ORIG ) )
    {
        state_ptr->step         = DEFAULT_STEP;
        state_ptr->top_left_x   = DEFAULT_TOP_LEFT_X;
        state_ptr->top_left_y   = DEFAULT_TOP_LEFT_Y;

        changes = true;
    }

    return changes;
}