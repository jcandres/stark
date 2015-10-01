#include "entity.h"

//static List entities;

Entity entity_new() {
	static int __ids = 0;

	Entity e = calloc(1, sizeof(struct entity));

	e->id = ++__ids;
	e->_remove = 0;

	e->x = 0;
	e->y = 0;

	e->sprite = NULL;
	e->image_index = 0;
	e->image_speed = 0;

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
	sprite_draw(e->sprite, (int)e->image_index, e->x, e->y);
	sprite_draw(e->sprite, (int)e->image_index, e->x, e->y);
}
