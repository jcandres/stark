
/**
 *
 * Entites are any persistent object -
 * They can be created, destroyed, and interacted with
 *
 */


// ideally they should be managed
// and have a handle easy to use ("player") like in haxepunk ...
// .. and a flag to avoid spawning more than one w/ the same handle, etc


#ifndef ENTITY_H
#define ENTITY_H

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
	float 	x, y;

	int 	_remove; //delete flag

	void*	sprite; //attached graphic
	float 	image_index, image_speed;

	///todo gamemaker draw stuff
} entity;

typedef entity* Entity;

Entity 	entity_new();
void 	entity_delete(Entity e);
void 	entity_update(Entity e);
void 	entity_draw(Entity e);

#endif
