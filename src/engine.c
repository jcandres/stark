#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

void engine_init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
	}

	screen_init("Title", 800, 600);

	atexit(SDL_Quit);
}

void engine_run() {
	Entity e = entity_new();
	int frames[] = {0, 1, 2, 1, NULL};
	e->sprite = sprite_new("mag/res/gfx.bmp", 8, 8, "0121");

	while (1) {
		if (input_update()) {break;}

		entity_draw(e);

		screen_render();

		SDL_Delay(100);
	}

}

void engine_end() {
}
