
/**
 * Graphic.h includes window and screen handling
 * and sprite loading and rendering
 *
 * Supports .bmp natively (magenta (255,0,255) xFF00FF will be replaced by alpha!)
 * Also .png if libpng16-16.dll is present
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
typedef struct sprite sprite;
typedef struct sprite* Sprite;

struct sprite {
	SDL_Texture* 	texture;
	String		name;
	int 		w, h; 				//tile size
	int 		row, col; 			//tile position on spritesheet
	int 		sheet_w, sheet_h;		//size of texture
	int 		sheet_cols, sheet_rows;		//size of texture

	String 		anim_sequence;			//sequence of frames to animate: "1, 2, 5, 1"
	float		anim_index,			//frame to draw
	                anim_speed,			//seconds
	                xscale, yscale,
	                angle;
	int		anim_number; 			//max of frames in the sequence
	void	(*anim_callback)(Sprite self);			//end of animation callback

	int 		depth;				//rendering depth
	Color		color;				//r g b a
	bool		flip;				//horizontal mirroring

	//private
	long	_oldtime; 	//animation time leftovers

};


Sprite 	sprite_new(String path, int w, int h, String frame_sequence, float speed);
void 	sprite_delete(Sprite s);
bool 	sprite_update(Sprite s);
bool 	sprite_draw(Sprite s, int x, int y);

void 	sprite_set_scale(Sprite s, float xscale, float yscale);
void 	sprite_set_speed(Sprite s, float seconds);
void 	sprite_set_callback(Sprite s, void (*func)(Sprite self));




#endif
