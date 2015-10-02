#include "screen.h"

bool screen_init(const char* title, int w, int h) {
	scr_zoom = 1;
	win_title = title;
	win_w = w;
	win_h = h;

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {debug("failed to init vide, %s", SDL_GetError());}

	window = SDL_CreateWindow(title,  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                          win_w, win_h, 0);
	if (!window) { debug("failed to create window, %s", SDL_GetError()); return false; }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) { debug("failed to create renderer, %s", SDL_GetError()); return false; }
	SDL_RenderSetLogicalSize(renderer, win_w * scr_zoom, win_h * scr_zoom);

	screen = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window),
	                           SDL_TEXTUREACCESS_TARGET, win_w, win_h);
	if (!screen) { debug("failed to create screen texture, %s", SDL_GetError()); return false; }

	return true;
}

bool screen_render() {
	/*
	SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
	SDL_SetRenderTarget(renderer, screen);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetTextureBlendMode(screen, SDL_BLENDMODE_NONE);

	SDL_RenderCopy(renderer, screen, NULL, NULL);
	*/

	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);

	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
	SDL_RenderClear(renderer); //clear for next iteration

	return true;
}


SDL_Surface* screen_optimize_surf(SDL_Surface* surf) {
	SDL_Surface* opt = SDL_ConvertSurfaceFormat(surf, SDL_GetWindowPixelFormat(window), 0);
	if (opt) {
		SDL_FreeSurface(surf);
		return opt;
	}
	return surf;
}
