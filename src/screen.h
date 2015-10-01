#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include "stark.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* screen;

int 	win_w, win_h;
const char* win_title;
int 	scr_zoom;

//todo buffer

bool 	screen_init(const char* title, int w, int h);
bool 	screen_render();
//todo resert (on resize, on fullscreen)

SDL_Surface* screen_optimize_surf(SDL_Surface* surf);

#endif
