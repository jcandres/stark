#ifndef SCENE_H
#define SCENE_H

#include "list.h"
#include "entity.h"

/**
 * scenes are collection of entities
 * usually only one scene is active
 */


typedef struct scene {
	List entities; //List of added entities
	List _add_list;
} scene;

typedef scene* Scene;


Scene	scene_new();
void	scene_free(Scene scn);
void 	scene_add(Scene scn, Entity ent); //add entity to scene
void 	scene_update(Scene scn); //iterate and update entities

#endif
