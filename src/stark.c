#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "stark.h"

#include "graphic.h"
#include "audio.h"
#include "input.h"
#include "entity.h"

#include "list.h"

/** Private */

bool 	stark_quit();
void	get_fps();


/** Game systems */

bool
stark_init(String title, int w, int h) {
	SDL_Init(0);

	if (!screen_init(title, w, h, 1)) { return false; }
	if (!audio_init()) { return false; }
	if (!input_init()) { return false; }
	//etc

	atexit(SDL_Quit);
	return true;
}

void cb(Sprite self) {
	(void)self; //avoid warning
	// Sound s = sound_load("res/popo.wav");
	// sound_play(s, 100);
}

bool
stark_execute() {

	///////////
	Entity e = entity_new("ee", 20, 20);
	Entity f = entity_new("FFFF", 30, 10);
	e->sprite = sprite_new("res/gfx.bmp", 8, 8, "0, 1, 2, 1", .25);
	sprite_set_scale(e->sprite, 10, 10);
	//f->sprite = sprite_new("res/bg.png", 0, 0, 0, 0);
	f->sprite = text_new("res/kimberley.ttf", "hi hi bbbb", 50, 0);
	////////////
	Music m = music_load("res/notes.wav");
	music_play(m, true, 5);
	sprite_set_callback(f->sprite, cb);

	while (1) {
		if (!input_update()) { break; }

		if (input_pressed(KEY_ESCAPE)) {break;} //debug hack

		get_fps();
		entity_update(e); /////////
		entity_update(f); /////////
		entity_draw(e); /////////
		entity_draw(f); /////////

		screen_render();
	}

	entity_delete(e);////
	entity_delete(f);////

	return stark_quit();
}


bool
stark_quit() {
	screen_quit();
	audio_quit();
	input_quit();

	return 0; //success, whatever
}


/** Private */

void
get_fps() {
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
		sprintf(s, "%s (%i fps)", screen_get_window_title(), fps_current);
		screen_set_window_title(s);
	}
}
