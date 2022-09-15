/*
-------------------------- notice --------------------------
| This code is from https://github.com/Glowman554/command  |
------------------------------------------------------------
*/

#include <argv_splitter.h>
#include <stdlib.h>
#include <string.h>

char** argv_split(char* str) {
	int len = strlen(str);

	int argc = 1;

	for (int i = 0; i < len; i++) {
		if(str[i] == ' ') {
			argc++;
		}
	}

	char** argv = malloc(sizeof(char*) * (argc + 1));

	argc = 1;
	argv[0] = &str[0];

	for (int i = 0; i < len; i++) {
		if(str[i] == ' ') {
			argv[argc] = &str[i + 1];
			str[i] = 0;
			argc++;
		}
	}

	return argv;
	
}