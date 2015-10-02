#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "list.h"

#include "stark.h"
#include "screen.h"
#include "audio.h"
#include "input.h"
#include "scene.h"
#include "entity.h"


bool 	stark_init();
bool 	stark_end();
void	get_fps();

bool stark_execute() {
	if (!stark_init()) { return false; }

	///////////
	Entity e = entity_new("test entity >:0", 200, 200);
	e->sprite = sprite_new("res/gfx.bmp", 8, 8, "012321");
	sprite_set_scale(e->sprite, 20, 20);
	////////////

	Sound s = sound_load("res/popo.wav");
	Music m = music_load("res/notes.wav");
	sound_play(s, 10);
	music_play(m, true, 30);


	while (1) {
		if (!input_update()) { break; }

		if (input_pressed(KEY_ESCAPE)) {break;} //debug hack
		if (input_pressed(KEY_SPACE)) {sound_play(s, 100);} //debug hack
		get_fps();
		entity_update(e); /////////
		entity_draw(e); /////////


		screen_render();
	}


	return stark_end();
}


bool stark_init() {
	SDL_Init(0);

	screen_init("Title", 800, 600);
	input_init();
	audio_init();
	//etc

	atexit(SDL_Quit);
	return true;
}

bool stark_end() {
	return SUCCESS;
}


void get_fps() {
	static float FPS_INTERVAL = 1.0 ;//seconds.
	static unsigned int fps_lasttime = 0; //the last recorded time.
	static unsigned int fps_current = 0; //the current FPS.
	static unsigned int fps_frames = 0; //frames passed since the last recorded fps.
	fps_frames++;
	if (fps_lasttime < SDL_GetTicks() - FPS_INTERVAL * 1000) {
		fps_lasttime = SDL_GetTicks();
		fps_current = fps_frames;
		fps_frames = 0;
		char s[80];
		sprintf(s, "%s (%i fps)", win_title, fps_current);
		SDL_SetWindowTitle(window, s);
	}
}
