#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
//#include <SDL_ttf.h>
#include "stark.h"

/**
 * Graphic.h includes window and screen handling
 * and sprite loading and rendering
 */

/** Window and Screen */
SDL_Window* window;
SDL_Renderer* renderer;

int 	win_w, win_h;
const char* win_title;
int 	scr_zoom;

bool 	screen_init(const char* title, int w, int h, int zoom);
bool 	screen_render();
void 	screen_quit();

/**
 * Types
 */
typedef SDL_Rect* Rect;
typedef SDL_Color* Color;


/** Sprites are 2D images, with animation capabilities */
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
bool 	sprite_draw(Sprite s, int x, int y);

void 	sprite_set_scale(Sprite s, float xscale, float yscale);




#endif
