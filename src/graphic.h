#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include "list.h"

typedef SDL_Rect Rect;

/** sprites are 2D images, animated */
typedef struct sprite {
	SDL_Texture* texture;
	int 		w, h; 				//tile size
	int 		row, col; 			//tile position on spritesheet
	int 		sheet_w, sheet_h;		//size of texture
	int 		sheet_cols, sheet_rows;		//size of texture

	const char* 	frames;				//ARRAY of frames
	float		frame_index;			//frame to draw
	float		animation_speed;		//

	float		current_frame, animation_speed,
	                xscale, yscale,
	                color, alpha, angle;

	//scale
	//angle
	//flip
} sprite;

typedef struct sprite* Sprite;

Sprite 	sprite_new(const char* path, int w, int h, const char* frames);
void 	sprite_free(Sprite s);
void 	sprite_update(Sprite s);
void 	sprite_draw(Sprite s, int frame, int x, int y);


/** animations organize frames inside a given sprite */
typedef struct animation {
	Sprite sprite;
	int w, h;
	List frames; //list of Rects
} animation;

typedef struct animation* Animation;



#endif
