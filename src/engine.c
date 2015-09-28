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
	e->sprite = sprite_new("mag/res/bg.bmp", 16, 16);

	while (1) {
		if (input_update()) {break;}

		entity_draw(e);

		screen_render();
	}

}

void engine_end() {
}
