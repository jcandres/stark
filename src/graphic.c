#include "graphic.h"
#include "screen.h"

SDL_Texture* load_texture(string path) {
	SDL_Surface* tmp = SDL_LoadBMP(path);
	if (!tmp) { debug("error loading texture: %s", path); return NULL;}

	//format + key magenta to alpha
	tmp = SDL_ConvertSurfaceFormat(tmp, SDL_GetWindowPixelFormat(window), 0);
	SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 0, 255));

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}

Sprite sprite_new(string path, int frame_w, int frame_h, string frame_sequence) {
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

	// sequence of frames
	s->frame_sequence = NULL;
	s->frame_index = 0;
	s->frame_rate = 500;

	s->_oldtime = 0;
	s->_frame_index = 0;
	s->_frames_max = 0;

	if (frame_sequence) { //user provided string, parse it
		strmk(s->frame_sequence, "%s", frame_sequence);
		//iterate the string sequence to check if well formed...
		for (char* i = s->frame_sequence; *i != '\0'; i++) {
			if (*i > '9' || *i < '0') {
				warning("possible bad sequence of frames in %s: %s, \
					make sure you are using numbers only",
				        s->name, s->frame_sequence);
			}
			s->_frames_max++;//increase frame count
		}
	}

	s->xscale = s->yscale = 1;
	s->alpha = 256;
	s->angle = 0;
	s->flip = true;

	return s;
}

void sprite_delete(Sprite s) {
	if (s->texture) { SDL_DestroyTexture(s->texture); }
	free(s);
	s = NULL;
}

bool sprite_update(Sprite s) {
	if (!s) { return false; }

	return true;
}

bool sprite_draw(Sprite s, int frame, int x, int y) {
	if (!s) { return false; }


	int draw_frame = (int)s->_frame_index; // the frame we will draw
	// ANIMATION STUFF
	/*
	int draw_frame = s->_frame_index; // the frame we will draw
		if (s->frame_sequence) {
			s->frame_index += s->frame_rate;
			//if reached end of animation...
			if (s->frame_sequence[(int)s->frame_index] == '\0') {
				// simply loop it (WIP)
				s->frame_index = 0;
			}
			draw_frame = chtoi(s->frame_sequence[(int)s->frame_index]);
		}*/
	//trace("%i\n", draw_frame);


	//get x and y of tile based on current frame + cols and rows of the texture..

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


	//update frame
	if (s->_oldtime + s->frame_rate > SDL_GetTicks()) { return true; }
	s->_oldtime = SDL_GetTicks();
	s->_frame_index += s->frame_rate;
	if (s->_frame_index >= s->_frames_max) {
		s->_frame_index = 0;
	}
	trace("%i", s->_frame_index);
	trace("x y %i %i", tile_x, tile_y);


	return true;
}

void sprite_set_scale(Sprite s, float xscale, float yscale) {
	s->xscale = xscale;
	s->yscale = yscale;
}

