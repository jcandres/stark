#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "stark.h"
#include "keys.h"

int 	mouse_x, mouse_y;

bool 	input_check(Key k);
bool 	input_pressed(Key k);
bool 	input_released(Key k);

bool 	input_init();
bool 	input_update(); //false if EXIT

//callbacks here
//virtual void onKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode) { } ; etc etc
//virtual void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value) { } ;

#endif
