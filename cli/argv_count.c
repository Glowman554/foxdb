/*
-------------------------- notice --------------------------
| This code is from https://github.com/Glowman554/command  |
------------------------------------------------------------
*/

#include <argv_count.h>

#include <stddef.h>

int argv_count(char* argv[]) {
	int argc = 0;

	while(argv[argc] != NULL) {
		argc++;
	}

	return argc;
}