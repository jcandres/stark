#include "input.h"
#include "list.h"

#define _MAX_STORED_KEYS 1024

SDL_Event event;

typedef enum {
	NONE,
	PRESSED,
	RELEASED
} key_state;

key_state keystates[_MAX_STORED_KEYS] = { NONE };
const Uint8* keyboard;


int input_check(Key k) {
	return (keyboard[SDL_GetScancodeFromKey(k)]);
}

int input_pressed(Key k) {
	return (keystates[k] == PRESSED);
}

int input_released(Key k) {
	return (keystates[k] == RELEASED);
}


int input_update() {
	keyboard = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < _MAX_STORED_KEYS; i++) { //reset states
		keystates[i] = NONE;
	}


	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_QUIT: return 1; break;
		case SDL_MOUSEMOTION:
			mouse_x = event.motion.x;
			mouse_y = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			///todo
			break;
		case SDL_KEYDOWN:
			if (!event.key.repeat) {
				keystates[event.key.keysym.sym] = PRESSED;
			}
			break;
		case SDL_KEYUP:
			if (!event.key.repeat) {
				keystates[event.key.keysym.sym] = RELEASED;
			}
			break;
		}
	}

	if (input_pressed(KEY_ESCAPE)) {return 1;} //debug hack

	return 0;
} //1 if EXIT
