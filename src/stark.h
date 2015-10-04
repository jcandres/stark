#ifndef STARK_H
#define STARK_H

/**
 *
 * 		STARK is a framework for easing game development.
 *
 *	 		http://suckless.org/philosophy
 *
 *
 * Provides boilerplate code to build apps on top of the library SDL2, taking
 * care of entity management, input checking, sprite display and animation,
 * sound and music playing, etc.

		#include "stark.h"

		int main(int argc, char* argv[]) {
			stark_init();

			//you code here.
			Entity player = new_entity("player", 20, 20);
			entity_set_sprite(player, new_sprite("gfx/popo.png"));
			entity_set_AI(player, my_player_function);

			return stark_execute();
		}

 * Stark provides some syntax sugar, with types such as bool and String. Types
 * that are pointers are capitalized: String, Entity, Sprite. Some preprocessor
 * macros are provided, such as debug() and trace()
 *
 * Stark should be linked statically, so the executable will be chubby but the
 * final release won't be a mess of .dll files.
 * Otherwise, it should have compile switchs for using less libraries - for
 * example, if I won;t be loading .png files, using the internal .bmp loader
 * instead of the whole SDL_image library. Same for SDL_ttf when using bitmap
 * fonts, and mp3 support when using only wav files.
 *
 * Finally, Stark should be as portable as SDL is.
 */


/* STYLE http://suckless.org/style */

#include <SDL2/SDL.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** syntax */
typedef enum { false, true } bool;

/** debug */
#define debug(M, ...) printf( "\nDEBUG %s:%s:%d:\n  " M "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#define warning(M, ...) printf( "\nWARNING %s:%s:%d:\n  " M "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#define trace(M, ...) printf(  M "\n", ##__VA_ARGS__) //for quick tests


/** Math */

/** returns the % of value over max_value: percent(128, 256) == 50
 * acceps and returns positive and negative values! */
static inline int percent(int value, int max_value) {
	if (max_value == 0) { return 0; }
	return (value * 100) / max_value;
}


/** String tools */
// move this to a sensible place plz

typedef char* String;

#define itoch(i) ( i + '0')
#define chtoi(ch) ( ch - '0')

static inline String 	string_new(const String s);
static inline void	string_delete(String s);
static inline String 	string_get_filename_name(const String filename);
static inline String 	string_get_filename_ext(const String filename);
static inline int 	asprintf(char**, char*, ...);
static inline int 	vasprintf(char**, char*, va_list);

/** Create alocated string: String s = string_new("hi"); */
static inline
String
string_new(const String s) {
	String d = malloc(strlen(s) + 1);     // Space for length plus '\0'
	if (d == NULL) { return NULL; }      // No memory
	strcpy(d, s);                        // Copy the characters
	return d;                            // Return the new String
}

/** Delete allocated String */
static inline
void
string_delete(String s) {
	free(s);
}

/** Safely compare strings */
static inline
bool
string_equals(const char* a, const char* b) {
	return strcmp(a, b) == 0;
}

/** Write formatted data to string - UNSAFE, use sasprintf */
static inline
int
asprintf(char** sptr, char* fmt, ...) {
	int retval;
	va_list argv;
	va_start(argv, fmt);
	retval = vasprintf(sptr, fmt, argv);
	va_end(argv);
	return retval;
}

static inline
int
vasprintf(char** sptr, char* fmt, va_list argv) {
	int wanted = vsnprintf(*sptr = NULL, 0, fmt, argv);
	if ((wanted < 0) || ((*sptr = malloc(1 + wanted)) == NULL)) {
		return -1;
	}

	return vsprintf(*sptr, fmt, argv);
}

/** Return "file.jpg" from "path/file.jpg" */
static inline
String
string_get_filename_name(const String filename) {
	String dot = strrchr(filename, '/');
	if (!dot || dot == filename) { return ""; }
	return dot + 1;
}

/** Return ".jpg" from "path/file.jpg" - including the . */
static inline
String
string_get_filename_ext(const String filename) {
	String dot = strrchr(filename, '.');
	if (!dot || dot == filename) { return ""; }
	return dot;
}

/** Safer asprintf - write formatted data into string
 * Sasprintf(q, "%s %s where col%i is not null", q, tablename, i); */
#define sasprintf(write_to, ...) { \
	char *tmp_string_for_extend = (write_to); \
	asprintf(&(write_to), __VA_ARGS__); \
	free(tmp_string_for_extend); \
}

/** String make. Allocates formatted string + data: strmk(greeting, "hello, %s", name);*/
#define strmk(write_to, ...) { \
	char *tmp = (write_to); \
	asprintf(&(write_to), __VA_ARGS__); \
	free(tmp); \
}

/**
 * the THING starts here
 */

/** the main method of the engine, moves all other components */
bool 	stark_init(String title, int w, int h);
bool 	stark_execute();


#endif
