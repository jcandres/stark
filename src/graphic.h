#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include "stark.h"
#include "list.h"

typedef SDL_Rect Rect;

/** sprites are 2D images, animated */
typedef struct sprite {
	SDL_Texture* texture;
	int 		w, h; 				//tile size
	int 		row, col; 			//tile position on spritesheet
	int 		sheet_w, sheet_h;		//size of texture
	int 		sheet_cols, sheet_rows;		//size of texture

	int 		depth;				//rendering depth

	const char* 	frames;				//ARRAY of frames
	float		frame_index;			//frame to draw

	float		current_frame, animation_speed,	//(int)current_frame
	                xscale, yscale;
	int		alpha;				//0-255
	float 		angle;
	bool		flip;				//horizontal mirroring

	//scale
	//angle
	//flip
} sprite;

typedef struct sprite* Sprite;

Sprite 	sprite_new(const char* path, int w, int h, const char* frames);
void 	sprite_delete(Sprite s);
bool 	sprite_update(Sprite s);
bool 	sprite_draw(Sprite s, int frame, int x, int y);






#endif
