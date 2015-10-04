
/**
 *
 * Audio.h takes care of initing sound systems, loading and
 * playing sfx and music. A wrapper around SDL_mixer.
 *
 * SDL_mixer allows for 16 sound channels + 1 music channel
 * Can play multiple sounds at once, but only one music.
 *
 * Supports .wav .riff .voc natively, .mid if native midi hardware
 * .mp3 if smpeg2.dll is present (beware some .mp3 files may need re-encoding!)
 * .ogg support available by having libogg-0.dll libvorbis-0.dll and libvorbisfile-3.dll
 *
 */

/**
 * FOR FUCKS SAKE sounds should be managed... you don't have to worry about
 * loading twice the same file and whatnot - simply call play("s.wav")
 * and the engine loads it if necessary
 */


#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>

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
Sound	sound_load(String path);
void	sound_delete(Sound snd);
void	sound_play(Sound snd, int volume); //volume is percent

///todo sound callbacks


/** Music

	Music m = music_load("res/notes.wav");
	music_play(m, true, 30);

Gotcha: if you queue manually a music fade out + in
	music stop(5);
	music_play(z, true, 2);
it'll BLOCK the game until the current fade out ends - this can be cool for
dramatic music changes, but otherwise use music_queue(z, true, 5, 2);
*/

Music	music_load(String path);
void	music_delete(Music mus);
void	music_play(Music mus, bool loop, float fade_in_seconds);
void	music_stop(float fade_out_seconds);
void	music_queue(Music mus, bool loop, float fade_out_seconds, float fade_in_seconds); //non blocking goodness
void	music_pause();
void	music_resume();
void	music_set_volume(int volume);

///todo music callbacks

#endif
