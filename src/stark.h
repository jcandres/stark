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

 * Stark provides some syntax sugar, with types such as bool and string. Types
 * that are pointers to a game component are capitalized: Entity, Sprite. Some
 * preprocessor macros are provided, such as debug() and trace()
 *
 * Stark should be linked statically, so the executable will be chubby but the
 * final release won't be a mess of .dll files.
 *
 * Finally, Stark should be as portable as SDL is.
 *
 */


/* STYLE http://suckless.org/style */

#include <SDL.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/** syntax */
typedef enum { false, true } bool;

/** debug */
#define debug(M, ...) printf( "\nDEBUG %s:%d:\n  " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define warning(M, ...) printf( "\nWARNING %s:%d:\n  " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define trace(M, ...) printf(  M "\n", ##__VA_ARGS__) //for quick tests

/**
 * returns the % of value over max_value: percent(128, 256) == 50
 * acceps positive and negative values
 */
static inline int percent(int value, int max_value) {
	if (max_value == 0) { return 0; }
	return (value * 100) / max_value;
}

/** string tools */
/* move this to a sensible place plz */
typedef char* string;

#define itoch(i) ( i + '0')
#define chtoi(ch) ( ch - '0')

static inline int asprintf(char**, char*, ...);
static inline int vasprintf(char**, char*, va_list);

static inline int vasprintf(char** sptr, char* fmt, va_list argv) {
	int wanted = vsnprintf(*sptr = NULL, 0, fmt, argv);
	if ((wanted < 0) || ((*sptr = malloc(1 + wanted)) == NULL)) {
		return -1;
	}

	return vsprintf(*sptr, fmt, argv);
}

static inline int asprintf(char** sptr, char* fmt, ...) {
	int retval;
	va_list argv;
	va_start(argv, fmt);
	retval = vasprintf(sptr, fmt, argv);
	va_end(argv);
	return retval;
}

/**
 * Safer asprintf macro - for appending strings
 * Sasprintf(q, "%s %s where col%i is not null", q, tablename, i);
 */
#define sasprintf(write_to, ...) { \
	char *tmp_string_for_extend = (write_to); \
	asprintf(&(write_to), __VA_ARGS__); \
	free(tmp_string_for_extend); \
}

#define strmk(write_to, ...) { \
	char *tmp = (write_to); \
	asprintf(&(write_to), __VA_ARGS__); \
	free(tmp); \
}
static inline char* strdup(const char* s) {
	char* d = malloc(strlen(s) + 1);     // Space for length plus nul
	if (d == NULL) { return NULL; }      // No memory
	strcpy(d, s);                        // Copy the characters
	return d;                            // Return the new string
}

static inline bool string_equals(char* a, char* b) {
	return strcmp(a, b) == 0;
}


/**
 * the THING starts here
 */

/** the main method of the engine, moves all other components */
bool 	stark_init();
bool 	stark_execute();


#endif
