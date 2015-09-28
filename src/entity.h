#ifndef ENTITY_H
#define ENTITY_H

#include "graphic.h"


typedef struct entity {
	int id;
	float x, y;

	int _remove; //delete flag

	Sprite sprite;
	Animation animation;

	///todo gamemaker draw stuff
} entity;

typedef entity* Entity;

Entity 	entity_new();
void 	entity_free(Entity e);
void 	entity_draw(Entity e);

#endif
