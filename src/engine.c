#include "engine.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* screen;

int win_w, win_h;
int scr_zoom;
const char* title;

void engine_init() {
	win_w = 800;
	win_h = 600;
	scr_zoom = 1;
	title = "Title";

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(title,  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                          win_w, win_h, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, scr_zoom, scr_zoom);
	screen = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window),
	                           SDL_TEXTUREACCESS_TARGET, win_w, win_h);

}

void engine_run() {
	while (1) {
		if (input_update()) {break;}
	}
}

void engine_end() {

}
