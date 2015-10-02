#ifndef STARK_H
#define STARK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


/** types */
typedef enum { false, true } bool;
#define SUCCESS 0
#define FAILURE -1

/** debug */
#define debug(M, ...) printf( "\nDEBUG %s:%d:\n  " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define warning(M, ...) printf( "\nWARNING %s:%d:\n  " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define trace(M, ...) printf(  M "\n", ##__VA_ARGS__) //for quick tests

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

#define strmk(write_to, ...) { \
	char *tmp = (write_to); \
	asprintf(&(write_to), __VA_ARGS__); \
	free(tmp); \
}

static inline bool string_equals(char* a, char* b) {
	return strcmp(a, b) == 0;
}


/**
 * the THING starts here
 */

/** the main method of the engine, moves all other components */
bool 	stark_execute();


#endif
