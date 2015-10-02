#include "graphic.h"

SDL_Texture* load_texture(string path);

/**
 * Screen handling
 */

bool
screen_init(const char* title, int w, int h, int zoom) {
	scr_zoom = 1;
	win_title = title;
	win_w = w;
	win_h = h;

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {debug("failed to init vide, %s", SDL_GetError());}

	window = SDL_CreateWindow(title,  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_w, win_h, 0);
	if (!window) { debug("failed to create window, %s", SDL_GetError()); return false; }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) { debug("failed to create renderer, %s", SDL_GetError()); return false; }

	if (zoom > 0) {
		scr_zoom = zoom;
		SDL_RenderSetLogicalSize(renderer, win_w / zoom, win_h / zoom);
	}

	//init true font
	//if (TTF_Init() < 0) { debug("TTF_Init: %s\n", TTF_GetError()); exit(2); }

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
	//TTF_Quit();
}


/**
 * Sprites
 */

Sprite
sprite_new(string path, int frame_w, int frame_h, string frame_sequence) {
	Sprite s = calloc(1, sizeof(struct sprite));

	s->name = NULL;
	strmk(s->name, "%s", path);

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

	s->depth = 0;

	// animation variables
	s->frame_sequence = NULL;
	s->frame_index = 0;
	s->frame_rate = .25;

	s->_oldtime = 0;
	s->_frames_max = 0;

	if (frame_sequence) { //user provided string, parse it
		strmk(s->frame_sequence, "");
		//iterate chars - if we have a number, append it to the array
		for (char* i = frame_sequence; *i != '\0'; i++) {
			int n = chtoi(*i);
			if (n >= 0 && n <= 9) {
				sasprintf(s->frame_sequence, "%s%i", s->frame_sequence, n);
				s->_frames_max++;//increase frame count
			}
		}
	}

	s->xscale = s->yscale = 1;
	s->alpha = 256;
	s->angle = 0;
	s->flip = true;

	return s;
}

void
sprite_delete(Sprite s) {
	if (s->texture) { SDL_DestroyTexture(s->texture); }
	free(s);
	s = NULL;
}

bool
sprite_update(Sprite s) {
	if (s->_oldtime + s->frame_rate * 1000 > SDL_GetTicks()) { return true; }
	s->_oldtime = SDL_GetTicks();
	s->frame_index++;
	if (s->frame_index >= s->_frames_max) {
		s->frame_index = 0;
	}

	return true;
}

bool
sprite_draw(Sprite s, int x, int y) {
	//get the frame we will draw from the string
	int draw_frame = chtoi(s->frame_sequence[(int)s->frame_index]);

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



/**
 * Private methods
 */

SDL_Texture*
load_texture(string path) {
	SDL_Surface* tmp = SDL_LoadBMP(path);
	if (!tmp) { debug("error loading texture: %s", path); return NULL;}

	//format + key magenta to alpha
	tmp = SDL_ConvertSurfaceFormat(tmp, SDL_GetWindowPixelFormat(window), 0);
	SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 0, 255));

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}
