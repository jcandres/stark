#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "stark.h"
#include "keys.h"

/** Input system */
bool 	input_init();
bool 	input_update(); //false if EXIT
void 	input_quit();


/** Input checking */
bool 	input_check(Key k);
bool 	input_pressed(Key k);
bool 	input_released(Key k);
int 	input_mouse_x();
int 	input_mouse_y();

//callbacks here
//virtual void onKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode) { } ; etc etc
//virtual void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value) { } ;

#endif
