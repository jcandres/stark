#include "entity.h"

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

void entity_free(Entity e) {
	free(e);
}

void entity_draw(Entity e) {
	e->image_index += e->image_speed;

	if (!e->sprite) { return; }
	sprite_draw(e->sprite, (int)e->image_index, e->x, e->y);
	sprite_draw(e->sprite, (int)e->image_index, e->x, e->y);
}
