
/**
 * Vector of pointers, resized dynamically
 *
 * to safely remove elements while iterating:

 	for (int i = 0; i != list_size(l); i++) {
		Entity e = list_get(l, i);
		if (!e->hp) {
			printf("dead entity: %s", e->name);
			list_pop_at(l, i);
			i--; 	//this is the magic bit
		}
	}

 */

#ifndef list_h
#define list_h

#include "stark.h"

struct list;
typedef struct list* List;

List 	list_new();
void	list_delete(List l);

void	list_push(List l, void* item);
void*	list_pop(List l);
void*	list_pop_at(List l, int index);
void	list_remove(List l, void* item); //remove all copies of item, not only first

void*	list_get(List l, int index);
void	list_set(List l, int index, void* item);

void	list_clear(List l); //reset to 0 items
int	list_is_empty(List l);
int	list_size(List l);


#endif
