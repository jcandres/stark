/*
#include "scene.h"

void update_actor_list();

Scene
scene_new() {
	Scene scn = calloc(1, sizeof(scene));

	scn->entities = list_new();
	scn->_add_list = list_new();

	return scn;
}

void
scene_delete(Scene scn) {
	list_clear_and_delete(scn->entities);
	free(scn->entities);
	list_clear_and_delete(scn->_add_list);
	free(scn->_add_list);
	free(scn);
	scn = NULL;
}

void
scene_add(Scene scn, Entity ent) {
	list_push(scn->_add_list, ent);
}

void
scene_update(Scene scn) {
	// update list
	while (list_size(scn->_add_list)) { //add
		list_push(scn->entities, list_pop(scn->_add_list));
	}

	List _remove_list = list_new(); //remove
	for (Entity* i = (Entity*)list_begin(scn->entities); i != (Entity*)list_end(scn->entities); i++) {
		if ((*i)->_remove) { list_push(_remove_list, *i); }
	}
	while (list_size(_remove_list)) {
		Entity e = list_pop(_remove_list);
		list_remove(scn->entities, e);
		entity_delete(e);
	}
	list_clear_and_delete(_remove_list);
	list_delete(_remove_list);
	// update list



	//update ents
	//draw

}

void update_actor_list() {

}
*/
