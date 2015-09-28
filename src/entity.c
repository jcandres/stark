#include "entity.h"

Entity entity_new() {
	static int __ids = 0;

	Entity e = calloc(1, sizeof(struct entity));

	e->id = ++__ids;
	e->_remove = 0;

	e->x = 0;
	e->y = 0;

	e->sprite = NULL;
	e->animation = NULL;

	return e;
}

void entity_free(Entity e) {
	free(e);
}

void entity_draw(Entity e) {
	if (!e->sprite) { return; }
	sprite_render(e->sprite);
}
