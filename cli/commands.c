#include <commands.h>
#include <stdio.h>
#include <foxdb.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#define no_args() if (argc != 1) { printf("Command takes no arguments!\n"); return false; }
#define x_args(x) if (argc != x + 1) { printf("Command takes %d arguments!\n", x); return false; }
#define x_or_more_args(x) if (argc < x + 1) { printf("Command takes %d+ arguments!\n", x); return false; }

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

void keys_it(foxdb_entry_t* e, uint64_t of) {
	printf("%s: %d@%ldB\n", e->key, e->type, e->size);
}

bool keys(int argc, char** argv) {
	no_args();

	assert(db != NULL);

	foxdb_iterate(db, keys_it);
	return true;
}


bool get(int argc, char** argv) {
	x_args(1);

	assert(db != NULL);

	foxdb_entry_t* e = foxdb_get(db, argv[1]);
	if (e) {
		switch(e->type) {
			case FOXDB_INT:
				printf("%d\n", ((foxdb_int_t*) e)->val);
				break;

			case FOXDB_BOOL:
				printf("%s\n", ((foxdb_bool_t*) e)->val ? "true" : "false");
				break;
			
			case FOXDB_FLOAT:
				printf("%f\n", ((foxdb_float_t*) e)->val);
				break;

			case FOXDB_STR:
				printf("%s\n", ((foxdb_str_t*) e)->val);
				break;
				
			case FOXDB_BIN:
				{
					foxdb_bin_t* bin = (foxdb_bin_t*) e;
					printf("%ld@%ldB\n", bin->cid, bin->size);
					for (int i = 0; i < bin->size; i++) {
						printf("%2x ", bin->val[i]);
					}
					printf("\n");
				}
				break;

			default:
				printf("Key %s has unknown type %d!\n", argv[1], e->type);
				break;
		}

		foxdb_del_entry(e);
	} else {
		printf("Key %s not found!\n", argv[1]);
	}

	return true;
}

bool new_str(int argc, char** argv) {
	x_or_more_args(2);

	assert(db != NULL);

	char str[512] = { 0 };
	for (int i = 2; i < argc; i++) {
		strcat(str, argv[i]);
		strcat(str, " ");
	}

	foxdb_str_t* e = foxdb_str(argv[1], str);

	db = foxdb_insert(db, (foxdb_entry_t*) e);

	foxdb_del_entry((foxdb_entry_t*) e);

	printf("Successfully added %s!\n", argv[1]);

	return true;
}

bool new_int(int argc, char** argv) {
	x_args(2);

	assert(db != NULL);

	int i = (int) strtol(argv[2], NULL, 10);
	foxdb_int_t* e = foxdb_int(argv[1], i);

	db = foxdb_insert(db, (foxdb_entry_t*) e);

	foxdb_del_entry((foxdb_entry_t*) e);

	printf("Successfully added %s!\n", argv[1]);

	return true;
}

bool new_bool(int argc, char** argv) {
	x_args(2);

	assert(db != NULL);

	bool b = strcmp(argv[2], "true") == 0;
	foxdb_bool_t* e = foxdb_bool(argv[1], b);

	db = foxdb_insert(db, (foxdb_entry_t*) e);

	foxdb_del_entry((foxdb_entry_t*) e);

	printf("Successfully added %s!\n", argv[1]);

	return true;
}
