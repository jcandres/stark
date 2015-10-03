#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphic.h"

typedef TTF_Font* Font;

/** Private */
Texture 	load_texture(String path);
Texture 	load_font(Font font, String path, Color col);


/** Screen system */

bool
screen_init(const char* title, int w, int h, int zoom) {
	scr_zoom = 1;
	win_title = title;
	win_w = w;
	win_h = h;

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {debug("failed to init SDL video, %s", SDL_GetError());}

	window = SDL_CreateWindow(title,  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_w, win_h, 0);
	if (!window) { debug("failed to create window, %s", SDL_GetError()); return false; }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) { debug("failed to create renderer, %s", SDL_GetError()); return false; }

	if (zoom > 0) {
		scr_zoom = zoom;
		SDL_RenderSetLogicalSize(renderer, win_w / zoom, win_h / zoom);
	}

	//Init SDL_image
	if (IMG_Init(IMG_INIT_PNG) < 0) {debug("failed to init SDL_image, %s", IMG_GetError());}

	//init SDL_ttf
	if (TTF_Init() < 0) { debug("TTF_Init: %s\n", TTF_GetError()); exit(2); }

	return true;
}

bool
screen_render() {
	/*
	SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
	SDL_SetRenderTarget(renderer, screen);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetTextureBlendMode(screen, SDL_BLENDMODE_NONE);

	SDL_RenderCopy(renderer, screen, NULL, NULL);
	*/

	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);

	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
	SDL_RenderClear(renderer); //clear for next iteration

	return true;
}

void
screen_quit() {
	IMG_Quit();
	TTF_Quit();
}


/** Sprites */

Sprite
sprite_new(String path, int frame_w, int frame_h, String anim_sequence, float speed) {
	Sprite s = calloc(1, sizeof(struct sprite));

	//init vars needed in all cases (animation, text..)
	s->name = string_new((path) ? path : "");
	s->xscale = s->yscale = 1.0;
	s->sheet_cols = s->sheet_rows = 1;

	//no filename = not loading graphic. Useful for creating text-only sprites.
	if (!path) {
		warning("no filename provided for Sprite %p", s);
		return s;
	}


	s->texture = load_texture(path);

	int tex_w, tex_h;
	SDL_QueryTexture(s->texture, NULL, NULL, &tex_w, &tex_h);

	//initialize texture and frame size
	s->sheet_w = s->w = tex_w;
	s->sheet_h = s->h = tex_h;

	//if user provided valid size, crop the frame size
	if (frame_w > 0 && frame_h > 0 && frame_w < tex_w && frame_h < tex_h) {
		s->w = frame_w;
		s->h = frame_h;
	}
	//get cols and rows
	s->sheet_cols = s->sheet_w / s->w;
	s->sheet_rows = s->sheet_h / s->h;

	//initialize animation vars
	if (anim_sequence) {
		s->anim_sequence = string_new("");
		//iterate chars - ignore all but numbers
		for (char* i = anim_sequence; *i != '\0'; i++) {
			int n = chtoi(*i);
			if (n >= 0 && n <= 9) {
				//valid frame: append to array, increase frame count
				sasprintf(s->anim_sequence, "%s%i", s->anim_sequence, n);
				s->anim_number++;
			}
		}
	}
	s->anim_speed = speed;

	return s;
}

void
sprite_delete(Sprite s) {
	if (s->name) { free(s->name); }
	if (s->texture) { SDL_DestroyTexture(s->texture); }
	if (s->anim_sequence) { free(s->anim_sequence); }
	if (s->color) { free(s->color); }
	free(s);
	s = NULL;
}

bool
sprite_update(Sprite s) {
	if (s->_oldtime + s->anim_speed * 1000 > SDL_GetTicks()) { return true; }
	s->_oldtime = SDL_GetTicks();
	s->anim_index++;
	if (s->anim_index >= s->anim_number) {
		s->anim_index = 0;
		if (s->anim_callback) { s->anim_callback(s); }
	}

	return true;
}

bool
sprite_draw(Sprite s, int x, int y) {
	//get the frame we will draw from the String
	int draw_frame = 0;
	if (s->anim_sequence) { draw_frame = chtoi(s->anim_sequence[(int)s->anim_index]); }

	int tile_x, tile_y;
	tile_x = (draw_frame % s->sheet_cols) * s->w;
	tile_y = (draw_frame / s->sheet_rows) * s->h;
	SDL_Rect clip = { tile_x, tile_y, s->w, s->h}; //x y WIPPP

	int w, h; //original texture size
	SDL_QueryTexture(s->texture, NULL, NULL, &w, &h);
	SDL_Rect dest = { x, y, s->w* s->xscale, s->h* s->yscale};

	SDL_RenderCopyEx(renderer, s->texture,
	                 &clip, &dest,
	                 (double)s->angle, //double angle
	                 NULL, //SDL_Point* center
	                 (s->flip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	return true;
}

void
sprite_set_scale(Sprite s, float xscale, float yscale) {
	if (xscale <= 0 || yscale <= 0) { return; }
	s->xscale = xscale;
	s->yscale = yscale;
}

void
sprite_set_speed(Sprite s, float seconds) {
	s->anim_speed = seconds;
}

void
sprite_set_callback(Sprite s, void (*func)(Sprite)) {
	s->anim_callback = func;
}


/** Fonts */

Sprite
text_new(String font_path, String text, int font_size, Color col) {
	Sprite s = sprite_new(0, 0, 0, 0, 0);
	Font fon = TTF_OpenFont(font_path, (font_size > 0) ? font_size : 14); //default size is 14px
	if (!fon) { debug("Error loading font: %s: %s", font_path, TTF_GetError()); }

	s->texture = load_font(fon, text, col);
	TTF_CloseFont(fon);

	sasprintf(s->name, "%s", text); //the name of this sprite is its text

	/** THIS IS A HACK UNTIL LOADING RESOURCES IS STREAMLINED */
	int tex_w, tex_h;
	SDL_QueryTexture(s->texture, NULL, NULL, &tex_w, &tex_h);
	//initialize texture and frame size
	s->sheet_w = s->w = tex_w;
	s->sheet_h = s->h = tex_h;
	s->sheet_cols = s->sheet_rows = 1;
	/** HACK ENDS HERE :( */

	return s;
}


/** Private */

Texture
load_texture(String path) {
	SDL_Surface* tmp = IMG_Load(path);
	if (!tmp) {
		debug("error loading texture: %s: %s", path, IMG_GetError());
		return NULL;
	}

	// .bmp files get magenta replaced by alpha !!!
	if (string_equals(string_get_filename_ext(path), ".bmp")) {
		SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 0, 255));
	}

	Texture tex = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}

Texture
load_font(Font font, String path, Color col) {
	SDL_Color c = {255, 255, 255, 255}; // white font by default
	if (col) { c = *col; }

	SDL_Surface* tmp = TTF_RenderText_Solid(font, path, c);
	//SDL_Surface* tmp = TTF_RenderText_Blended(font, path, c); //antialias - slow
	if (!tmp) {debug("error loading font texture: %s: %s", path, TTF_GetError()); }

	Texture tex = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}
