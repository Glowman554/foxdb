#include <commands.h>
#include <stdio.h>
#include <foxdb.h>
#include <stddef.h>
#include <assert.h>

#define no_args() if (argc != 1) { printf("Command takes no arguments!\n"); return false; }
#define x_args(x) if (argc != x + 1) { printf("Command takes %d arguments!\n", x); return false; }

void* db = NULL;

bool new_db(int argc, char** argv) {
	no_args();

	assert(db == NULL);
	db = foxdb_new();

	printf("Successfully created new db in memory!\n");
	return true;
}

bool load_db(int argc, char** argv) {
	x_args(1);

	assert(db == NULL);

	FILE* f = fopen(argv[1], "rb");
	db = foxdb_from_file(f);
	fclose(f);

	printf("Loaded db successfully from %s!\n", argv[1]);
	return true;
}

bool save_db(int argc, char** argv) {
	x_args(1);

	assert(db != NULL);

	FILE* f = fopen(argv[1], "wb");
	foxdb_to_file(db, f);
	fclose(f);

	printf("Saved successfully to %s!\n", argv[1]);
	return true;
}