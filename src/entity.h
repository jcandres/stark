
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

typedef struct entity entity;
typedef entity* Entity;

struct entity {
	int 	id;
	char*	name;

	int 	_remove; 	//delete flag

	int 	x, y;		//position component
	void*	sprite; 	//graphic component

	/*
		WIPPPPPPPP

	pointers to functions for user methods

	defaults to entity_update, which handles the 'standard' behaviour
	such as updating movement, drawing, etc

	use: myent->update = my_custom_update_funct;
	the function will be called instead of the default one
	to 'inherit' the default behaviour, just call it in the custom func
	*/

	void	(*update)(Entity e);
};


Entity 	entity_new(String name, int x, int y);
void 	entity_delete(Entity e);
void 	entity_update(Entity e); 		//the dafault update code
void 	entity_draw(Entity e); 			//the dafault draw code

//wip
Entity 	entity_get(String name);
Entity 	entity_get_at(int x, int y);


#endif
