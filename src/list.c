
#include "list.h"

#define _MIN(a,b) (((a)<(b))?(a):(b))
#define LIST(l) ((list_int_t *)l)

typedef struct list_int_t {
	void** array;
	int fillSize;
	int allocSize;
} list_int_t;

static void list_allocate_int(List l) {
	void** newArray;
	int newSize = LIST(l)->allocSize * 2;
	if (newSize == 0) { newSize = 16; }
	newArray = (void**)calloc(sizeof(void*), newSize);
	if (LIST(l)->array) {
		if (LIST(l)->fillSize > 0) { memcpy(newArray, LIST(l)->array, sizeof(void*)*LIST(l)->fillSize); }
		free(LIST(l)->array);
	}
	LIST(l)->array = newArray;
	LIST(l)->allocSize = newSize;
}

void list_set_size(List l, int size) {
	LIST(l)->fillSize = _MIN(size, LIST(l)->allocSize);
}

List list_new() {
	return (List)calloc(1, sizeof(list_int_t));
}

List list_allocate(int nb_elements) {
	List l = list_new();
	LIST(l)->array = (void**)calloc(sizeof(void*), nb_elements);
	LIST(l)->allocSize = nb_elements;
	return l;
}

List list_duplicate(List l) {
	int i = 0;
	void** t;
	list_int_t* ret = (list_int_t*)list_new();
	while (ret->allocSize < LIST(l)->allocSize) { list_allocate_int((List)ret); }
	ret->fillSize = LIST(l)->fillSize;
	for (t = list_begin(l); t != list_end(l); t++) {
		ret->array[i++] = *t;
	}
	return (List)ret;
}

void list_delete(List l) {
	if (l) {
		if (LIST(l)->array) { free(LIST(l)->array); }
		free(l);
	}
}

void list_push(List l, const void* elt) {
	if (LIST(l)->fillSize + 1 >= LIST(l)->allocSize) { list_allocate_int(l); }
	LIST(l)->array[LIST(l)->fillSize++] = (void*)elt;
}
void* list_pop(List l) {
	if (LIST(l)->fillSize == 0) { return NULL; }
	return LIST(l)->array[--(LIST(l)->fillSize)];
}
void* list_peek(List l) {
	if (LIST(l)->fillSize == 0) { return NULL; }
	return LIST(l)->array[LIST(l)->fillSize - 1];
}
void list_add_all(List l, List l2) {
	void** curElt;
	for (curElt = list_begin(l2); curElt != list_end(l2); curElt ++) {
		list_push(l, *curElt);
	}
}
void* list_get(List l, int idx) {
	return LIST(l)->array[idx];
}
void list_set(List l, const void* elt, int idx) {
	if (idx < 0) { return; }
	while (LIST(l)->allocSize < idx + 1) { list_allocate_int(l); }
	LIST(l)->array[idx] = (void*)elt;
	if (idx + 1 > LIST(l)->fillSize) { LIST(l)->fillSize = idx + 1; }
}
void** list_begin(List l) {
	if (LIST(l)->fillSize == 0) { return (void**)NULL; }
	return &LIST(l)->array[0];
}
void** list_end(List l) {
	if (LIST(l)->fillSize == 0) { return (void**)NULL; }
	return &LIST(l)->array[LIST(l)->fillSize];
}
void list_reverse(List l) {
	void** head = list_begin(l);
	void** tail = list_end(l);
	while (head < tail) {
		void* tmp = *head;
		*head = *tail;
		*tail = tmp;
		head++;
		tail--;
	}
}
void** list_remove_iterator(List l, void** elt) {
	void** curElt;
	for (curElt = elt; curElt < list_end(l) - 1; curElt ++) {
		*curElt = *(curElt + 1);
	}
	LIST(l)->fillSize--;
	if (LIST(l)->fillSize == 0) { return ((void**)NULL) - 1; }
	else { return elt - 1; }
}
void list_remove(List l, const void* elt) {
	void** curElt;
	for (curElt = list_begin(l); curElt != list_end(l); curElt ++) {
		if (*curElt == elt) {
			list_remove_iterator(l, curElt);
			return;
		}
	}
}
void** list_remove_iterator_fast(List l, void** elt) {
	*elt = LIST(l)->array[LIST(l)->fillSize - 1];
	LIST(l)->fillSize--;
	if (LIST(l)->fillSize == 0) { return ((void**)NULL) - 1; }
	else { return elt - 1; }
}
void list_remove_fast(List l, const void* elt) {
	void** curElt;
	for (curElt = list_begin(l); curElt != list_end(l); curElt ++) {
		if (*curElt == elt) {
			list_remove_iterator_fast(l, curElt);
			return;
		}
	}
}
int list_contains(List l, const void* elt) {
	void** curElt;
	for (curElt = list_begin(l); curElt != list_end(l); curElt ++) {
		if (*curElt == elt) { return 1; }
	}
	return 0;
}
void list_clear(List l) {
	LIST(l)->fillSize = 0;
}
void list_clear_and_delete(List l) {
	void** curElt;
	for (curElt = list_begin(l); curElt != list_end(l); curElt ++) {
		free(*curElt);
	}
	LIST(l)->fillSize = 0;
}
int list_size(List l) {
	return LIST(l)->fillSize;
}
void** list_insert_before(List l, const void* elt, int before) {
	int idx;
	if (LIST(l)->fillSize + 1 >= LIST(l)->allocSize) { list_allocate_int(l); }
	for (idx = LIST(l)->fillSize; idx > before; idx--) {
		LIST(l)->array[idx] = LIST(l)->array[idx - 1];
	}
	LIST(l)->array[before] = (void*)elt;
	LIST(l)->fillSize++;
	return &LIST(l)->array[before];
}
int list_is_empty(List l) {
	return (LIST(l)->fillSize == 0);
}
