#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "list.h"

#include "entity.h"
#include "input.h"
#include "scene.h"
#include "screen.h"

void engine_init();
void engine_run();
void engine_end();

//scene list, current scene, change scene...

#endif
