#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include "stark.h"
#include "list.h"

typedef SDL_Rect Rect;

typedef struct {
	unsigned int r, g, b;
} Color;


/** sprites are 2D images, animated */
typedef struct sprite {
	SDL_Texture* 	texture;
	string		name;
	int 		w, h; 				//tile size
	int 		row, col; 			//tile position on spritesheet
	int 		sheet_w, sheet_h;		//size of texture
	int 		sheet_cols, sheet_rows;		//size of texture

	int 		depth;				//rendering depth

	string 		frame_sequence;			//sequence of frames to animate: "0134"
	float		frame_index,			//frame to draw
	                frame_rate,			//milliseconds
	                xscale, yscale,
	                angle;
	unsigned int	alpha;				//0-255
	bool		flip;				//horizontal mirroring

	//private
	long	_oldtime; 	//animation time leftovers
	long	_frame_index; 	//the real deal
	int	_frames_max; 	//max of frames in the sequence

} sprite;

typedef struct sprite* Sprite;

Sprite 	sprite_new(string path, int w, int h, string frame_sequence);
void 	sprite_delete(Sprite s);
bool 	sprite_update(Sprite s);
bool 	sprite_draw(Sprite s, int frame, int x, int y);

void 	sprite_set_scale(Sprite s, float xscale, float yscale);




#endif
