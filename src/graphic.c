#include "graphic.h"

/** Private */
SDL_Texture* load_texture(String path);


/** SCREEN SYSTEM */

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


/** SPRITES */

Sprite
sprite_new(String path, int frame_w, int frame_h, String anim_sequence, float speed) {
	Sprite s = calloc(1, sizeof(struct sprite));

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

	//initialize animation vars
	if (anim_sequence) {
		strmk(s->anim_sequence, "");
		//iterate chars - if we have a number, append it to the array
		for (char* i = anim_sequence; *i != '\0'; i++) {
			int n = chtoi(*i);
			if (n >= 0 && n <= 9) {
				sasprintf(s->anim_sequence, "%s%i", s->anim_sequence, n);
				s->anim_number++;//increase frame count
			}
		}
	}
	s->anim_speed = speed;

	s->xscale = s->yscale = 1.0;

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
	int draw_frame = chtoi(s->anim_sequence[(int)s->anim_index]);

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


/** Private */

SDL_Texture*
load_texture(String path) {
	SDL_Surface* tmp = SDL_LoadBMP(path);
	if (!tmp) { debug("error loading texture: %s", path); return NULL;}

	//format + key magenta to alpha
	tmp = SDL_ConvertSurfaceFormat(tmp, SDL_GetWindowPixelFormat(window), 0);
	SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 0, 255));

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}
