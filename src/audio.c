#include "audio.h"


bool audio_init() {
	if (Mix_Init(0) < 0) {
		debug("failed to init audio, %s", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		debug("SDL_mixer could not initialize: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

void audio_quit() {
	Mix_Quit();
	Mix_CloseAudio();
}

/* SOUNDS */

Sound sound_load(string path) {
	Sound snd = Mix_LoadWAV(path);
	if (!snd) { debug("Cannot load sound: %s\n", path); }
	return snd;
}

void sound_delete(Sound snd) {
	Mix_FreeChunk(snd);
	snd = NULL;
}

void sound_play(Sound snd, int volume) {
	int v = (volume * MIX_MAX_VOLUME) / 100; // from %, get  0-128
	Mix_VolumeChunk(snd, v);
	Mix_PlayChannel(-1, snd, 0); 	//chan -1 defaults to next available channel
}


/* MUSIC */

Music music_load(string path) {
	Music mus = Mix_LoadMUS(path);
	if (!mus) { debug("Cannot load music: %s\n", path); }
	return mus;
}

void music_delete(Music mus) {
	Mix_FreeMusic(mus);
	mus = NULL;
}

void music_play(Music mus, bool loop, float fade_in_seconds) {
	Mix_FadeInMusic(mus, loop ? -1 : 1, fade_in_seconds * 1000);
}

void music_set_volume(int volume) {
	Mix_VolumeMusic((volume * MIX_MAX_VOLUME) / 100);
}

void music_pause() {
	Mix_PauseMusic();
}

void music_resume() {
	Mix_ResumeMusic();
}

void music_stop(float fade_out_seconds) {
	Mix_FadeOutMusic(fade_out_seconds * 1000);
}

