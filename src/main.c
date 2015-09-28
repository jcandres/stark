#include "engine.h"

int main(int argc, char* argv[]) {
	(void)argc; (void)argv; //supress warnings

	engine_init();
	engine_run();
	engine_end();

	return 0;
}
