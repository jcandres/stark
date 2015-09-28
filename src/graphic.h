#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include "list.h"

/** sprites are 2D images */

typedef struct sprite {
	SDL_Texture* texture;
} sprite;

typedef struct sprite* Sprite;

Sprite 	sprite_new(const char* filename);
void 	sprite_free(Sprite);
void 	sprite_render(Sprite);


/** animations organize frames inside a given sprite */
typedef struct animation {
	Sprite sprite;
	int w, h;
	List frames;
} animation;

typedef struct animation* Animation;



#endif
