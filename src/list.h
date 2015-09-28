#ifndef __LIST_H__
#define __LIST_H__


#include <string.h>
#include <stdlib.h>

typedef void* List;

List  list_new();
List  list_allocate(int nb_elements);
List  list_duplicate(List l);
void    list_delete(List l);
void    list_push(List l, const void* elt);
void*   list_pop(List l);
void*   list_peek(List l);
void    list_add_all(List l, List l2);
void*   list_get(List l, int idx);
void    list_set(List l, const void* elt, int idx);
void**  list_begin(List l);
void**  list_end(List l);
void    list_reverse(List l);
void**  list_remove_iterator(List l, void** elt);
void    list_remove(List l, const void* elt);
void**  list_remove_iterator_fast(List l, void** elt);
void    list_remove_fast(List l, const void* elt);
int    list_contains(List l, const void* elt);
void    list_clear(List l);
void    list_clear_and_delete(List l);
int     list_size(List l);
void**  list_insert_before(List l, const void* elt, int before);
int    list_is_empty(List l);

#endif // __LIST_H__
