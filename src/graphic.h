#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include "list.h"


/** sprites are 2D images */

typedef struct sprite {
	SDL_Texture* texture;
	int w, h;
} sprite;

typedef struct sprite* Sprite;

Sprite 	sprite_new(const char* path, int w, int h);
void 	sprite_free(Sprite s);
void 	sprite_render(Sprite s);


/** animations organize frames inside a given sprite */
typedef struct animation {
	Sprite sprite;
	int w, h;
	List frames; //list of SDL_Rect
} animation;

typedef struct animation* Animation;



#endif
