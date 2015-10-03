#include "entity.h"

/** Entity manager */

//todo static List entities;


/** Entities */

Entity
entity_new(string name, int x, int y) {
	static int __ids = 0;

	Entity e = calloc(1, sizeof(struct entity));

	e->id = ++__ids;
	e->_remove = 0;

	e->name = NULL;
	strmk(e->name, "%s", name);

	e->x = x;
	e->y = y;

	e->sprite = NULL;

	return e;
}

void
entity_delete(Entity e) {
	if (e->name) { free(e->name); }
	if (e->sprite) { sprite_delete(e->sprite); }
	free(e);
	e = NULL;
}

void
entity_update(Entity e) {
	if (e->sprite) { sprite_update(e->sprite); }
}

void
entity_draw(Entity e) {
	if (e->sprite) { sprite_draw(e->sprite, e->x, e->y); }
}
