
/**
 * Graphic.h includes window and screen handling
 * and sprite loading and rendering
 */


#ifndef GRAPHIC_H
#define GRAPHIC_H

//#include <SDL_ttf.h>
#include "stark.h"


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

	string 		anim_sequence;			//sequence of frames to animate: "1, 2, 5, 1"
	float		anim_index,			//frame to draw
	                anim_speed,			//seconds
	                xscale, yscale,
	                angle;
	int		anim_number; 			//max of frames in the sequence

	int 		depth;				//rendering depth
	Color		color;				//r g b a
	bool		flip;				//horizontal mirroring

	//private
	long	_oldtime; 	//animation time leftovers

} sprite;

typedef struct sprite* Sprite;

Sprite 	sprite_new(string path, int w, int h, string frame_sequence, float speed);
void 	sprite_delete(Sprite s);
bool 	sprite_update(Sprite s);
bool 	sprite_draw(Sprite s, int x, int y);

void 	sprite_set_scale(Sprite s, float xscale, float yscale);
void 	sprite_set_speed(Sprite s, float seconds);




#endif
