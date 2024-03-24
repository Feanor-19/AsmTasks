#ifndef HANDLERS
#define HANDLERS

#include "common.h"


//! @brief Handles events of the given window.
void handle_events( sf::Window &window );

//! @brief Handles keyboard, changes *state_ptr if needed.
//! @return true if *state_ptr was changed, 0 otherwise.
bool handle_keyboard( State *state_ptr );

#endif /* HANDLERS */