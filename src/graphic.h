
/**
 * Graphic.h includes window and screen handling
 * and sprite loading and rendering
 *
 * SDL supports .bmp natively (magenta (255,0,255) xFF00FF will be replaced with
 * alpha!), and SDL_image allows using .png files if libpng16-16.dll is present
 *
 * SDL_ttf used for rendering fonts, requires libfreetype-6.dll
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

/*maybe restrict to a public interface Graphic, that is a void* that can host
Sprites, Text, etc so the user only calls
graphic_draw(self->graphic);
then this function simply draws the texture inside the passed argument:
sprite_draw(self->texture), text_draw(self->texture), etc

IS THIS EVEN POSSIBL?? it would be v nice*/


Sprite 	sprite_new(String path, int w, int h, String frame_sequence, float speed);
void 	sprite_delete(Sprite s);
bool 	sprite_update(Sprite s);
bool 	sprite_draw(Sprite s, int x, int y);

void 	sprite_set_scale(Sprite s, float xscale, float yscale);
void 	sprite_set_speed(Sprite s, float seconds);
void 	sprite_set_callback(Sprite s, void (*func)(Sprite self));

/** texts are sprites generated from a font file and user text */
Sprite 	text_new(String font_path, String text, Color col, int font_size);



#endif
