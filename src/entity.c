#include "entity.h"

//static List entities;

Entity entity_new(string name, int x, int y) {
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

void entity_delete(Entity e) {
	free(e);
}

void entity_update(Entity e) {
	sprite_update(e->sprite);
}

void entity_draw(Entity e) {
	if (!e->sprite) { return; }
	sprite_draw(e->sprite, 0, e->x, e->y); //wippp image_index
}
