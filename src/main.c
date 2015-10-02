#include "stark.h"

int main(int argc, char* argv[]) {
	(void)argc; (void)argv; //supress warnings

	stark_init();

	return stark_execute();
}
