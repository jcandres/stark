
/**
 *
 * Entites are any persistent object - a container
 * They can be created, destroyed, and interacted with
 *
 * Components (graphics, ai) can be added with void*
 *
 */


// ideally they should be managed
// and have a handle easy to use ("player") like in haxepunk ...
// .. and a flag to avoid spawning more than one w/ the same handle, etc


#ifndef ENTITY_H
#define ENTITY_H

#include "stark.h"
#include "graphic.h"

/*
typedef struct {
	int type_id;
	void* (*new_func)();
	void (*del_func)();
} entity_handler;
*/


typedef struct entity {
	int 	id;
	char*	name;

	int 	_remove; 	//delete flag

	int 	x, y;		//position component
	void*	sprite; 	//graphic component
} entity;

typedef entity* Entity;

Entity 	entity_new(string name, int x, int y);
void 	entity_delete(Entity e);
void 	entity_update(Entity e);
void 	entity_draw(Entity e);

//wip
Entity 	entity_get(string name);
Entity 	entity_get_at(int x, int y);


#endif
