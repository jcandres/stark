#include "audio.h"

static Music 	mus_queued = NULL;
static bool 	mus_queued_loop = false;
static float 	mus_queued_fadein = 0;
void 	music_queue_callback();



bool
audio_init() {
	if (Mix_Init(MIX_INIT_MP3) < 0) {
		debug("failed to init audio, %s", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		debug("SDL_mixer could not initialize: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

void
audio_quit() {
	Mix_CloseAudio();
	Mix_Quit();
}

/* SOUNDS */

Sound
sound_load(string path) {
	Sound snd = Mix_LoadWAV(path);
	if (!snd) { debug("Cannot load sound: %s> %s\n", path, Mix_GetError()); }
	return snd;
}

void
sound_delete(Sound snd) {
	Mix_FreeChunk(snd);
	snd = NULL;
}

void
sound_play(Sound snd, int volume) {
	int v = percent(volume, MIX_MAX_VOLUME);
	Mix_VolumeChunk(snd, v);
	Mix_PlayChannel(-1, snd, 0); 	//chan -1 defaults to next available channel
}


/* MUSIC */

Music
music_load(string path) {
	Music mus = Mix_LoadMUS(path);
	if (!mus) { debug("Cannot load music: %s\n", path); }
	return mus;
}

void
music_delete(Music mus) {
	Mix_FreeMusic(mus);
	mus = NULL;
}

void
music_play(Music mus, bool loop, float fade_in_seconds) {
	if (Mix_FadeInMusic(mus, loop ? -1 : 1, fade_in_seconds * 1000) < 0) {
		debug("error playing / fading in music: %s", Mix_GetError());
	}
}

void
music_stop(float fade_out_seconds) {
	if (Mix_FadeOutMusic(fade_out_seconds * 1000) < 0) {
		debug("error stopping / fading out music: %s", Mix_GetError());
	}
}

void
music_queue(Music mus, bool loop, float fade_out_seconds, float fade_in_seconds) {
	mus_queued = mus;
	mus_queued_loop = loop;
	mus_queued_fadein = fade_in_seconds;
	Mix_HookMusicFinished(music_queue_callback);
	music_stop(fade_out_seconds);
}

void
music_set_volume(int volume) {
	Mix_VolumeMusic((volume * MIX_MAX_VOLUME) / 100);
}

void
music_pause() {
	Mix_PauseMusic();
}

void
music_resume() {
	Mix_ResumeMusic();
}


/**
 * private
 */

void
music_queue_callback() {
	music_play(mus_queued, mus_queued_loop, mus_queued_fadein);
}

