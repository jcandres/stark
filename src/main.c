#include "stark.h"

int main(int argc, char* argv[]) {
	(void)argc; (void)argv; //supress warnings

	stark_init("Stark engine", 800, 600);

	return stark_execute();
}
