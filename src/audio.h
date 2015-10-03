
/**
 *
 * Audio.h takes care of initing sound systems, loading and
 * playing sfx and music. A wrapper around SDL_mixer.
 *
 * SDL_mixer allows for 16 sound channels + 1 music channel
 * Can play multiple sounds at once, but only one music.
 *
 * Supports .WAV .RIFF .VOC natively
 * .MID if native midi hardware
 * .MOD and friends (may require .dll?)
 * .OGG by having libogg-0.dll libvorbis-0.dll and libvorbisfile-3.dll
 * .MP3 if smpeg2.dll is present (some .mp3 files will need re-encoding)
 *
 */


#ifndef SOUND_H
#define SOUND_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "stark.h"


typedef Mix_Chunk* Sound;
typedef Mix_Music* Music;

/** audio system */

bool 	audio_init();
void 	audio_quit();


/** Sounds

Sound s = sound_load("res/popo.wav");
sound_play(s, 10);
*/
Sound	sound_load(string path);
void	sound_delete(Sound snd);
void	sound_play(Sound snd, int volume); //volume is percent

///todo sound callbacks


/** Music

Music m = music_load("res/notes.wav");
music_play(m, true, 30);
*/

Music	music_load(string path);
void	music_delete(Music mus);
void	music_play(Music mus, bool loop, float fade_in_seconds);
void	music_stop(float fade_out_seconds);
void	music_queue(Music mus, bool loop, float fade_out_seconds, float fade_in_seconds); //non blocking goodness
void	music_pause();
void	music_resume();
void	music_set_volume(int volume);

///todo music callbacks

#endif
