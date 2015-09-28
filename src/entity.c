#include "entity.h"

Entity entity_new() {
	Entity e = calloc(1, sizeof(struct entity));

	e->x = 0;
	e->y = 0;

	return e;
}

void entity_free(Entity e) {
	free(e);
}
