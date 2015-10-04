
#include <math.h>
#include "list.h"

/** Private */
typedef struct list {
	int 	num_items, num_slots;
	void**	items;
} list;

static void list_reserve_more(List l);
static void list_reserve_less(List l);


/** List */

List
list_new() {
	List l = malloc(sizeof(struct list));
	l->num_items = l->num_slots = 0;
	l->items = malloc(sizeof(void*) * l->num_slots);
	return l;
}

void
list_delete(List l) {
	free(l->items);
	free(l);
	l = NULL;
}

void
list_push(List l, void* item) {
	l->num_items++;
	list_reserve_more(l);
	l->items[l->num_items - 1] = item;
}

void*
list_pop(List l) {
	if (l->num_items <= 0) { debug("tried to pop empty list: %p", l); }
	void* item = l->items[l->num_items - 1];

	l->num_items--;
	list_reserve_less(l);
	return item;
}

void*
list_pop_at(List l, int index) {
	if (l->num_items <= 0) { debug("tried to pop empty list: %p", l); }
	void* item = l->items[index];

	memmove(&l->items[index],
	        &l->items[index + 1],
	        sizeof(void*) * ((l->num_items - 1) - index));

	l->num_items--;
	list_reserve_less(l);
	return item;
}

void
list_remove(List l, void* item) {
	static int found = 0;
	for (int i = 0; i < l->num_items; i++) {
		if (item == l->items[i]) {
			list_pop_at(l, i);
			i--;
			//return;
		}
	}
}

void*
list_get(List l, int index) {
	if (index < 0 || index >= l->num_items) {
		debug("Index out of bounds for list %p", l); return NULL;
	}

	return l->items[index];
}

void
list_set(List l, int index, void* item) {
	if (index < 0 || index >= l->num_items) {
		debug("Index out of bounds for list %p", l); return;
	}

	l->items[index] = item;
}

void
list_clear(List l) {
	l->num_items = 0;
	l->num_slots = 0;
	l->items = realloc(l->items, sizeof(void*) * l->num_slots);
}

int
list_is_empty(List l) {
	return (!l->num_items);
}

int
list_size(List l) {
	return l->num_items;
}


/** Private */
/** Realloc functions for matching the current number of items */

static
void
list_reserve_more(List l) {
	if (l->num_items > l->num_slots) {
		l->num_slots = ceil((l->num_slots + 1) * 1.5);
		l->items = realloc(l->items, sizeof(void*) * l->num_slots);
	}
}

static
void
list_reserve_less(List l) {
	if (l->num_slots > pow(l->num_items + 1, 1.5)) {
		l->num_slots = floor((l->num_slots - 1) * (1.0 / 1.5));
		l->items = realloc(l->items, sizeof(void*) * l->num_slots);
	}
}
