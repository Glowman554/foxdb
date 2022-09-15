#pragma once

#include <stdint.h>
#include <stdbool.h>

#define FOXDB_MAGIC 0xf0DBBABE
#define FOXDB_KEY_MAX 64

typedef struct foxdb_file_header {
	uint32_t magic;
	uint64_t size;
} foxdb_file_header_t;

typedef struct foxdb_entry {
	uint64_t size;
	uint8_t type;

	char key[FOXDB_KEY_MAX];
} foxdb_entry_t;

#define DATA_STRUCT(name, entries) typedef struct { \
	foxdb_entry_t header; \
	entries; \
} name;

DATA_STRUCT(foxdb_int_t, int val);
DATA_STRUCT(foxdb_bool_t, bool val);
DATA_STRUCT(foxdb_str_t, char val[]);

enum foxdb_types {
	FOXDB_INT = 1,
	FOXDB_BOOL,
	FOXDB_STR,
};

typedef void (*foxdb_key_iterator)(foxdb_entry_t* e, uint64_t of);

void* foxdb_new();
void foxdb_del(void* foxdb);

void* foxdb_insert(void* foxdb, foxdb_entry_t* entry);
void* foxdb_remove(void* foxdb, const char* name);
foxdb_entry_t* foxdb_get(void* foxdb, const char* name); // returns copy of struct. NEEDS TO BE FREED WITH A CALL TO foxdb_del_entry
void foxdb_iterate(void* foxdb, foxdb_key_iterator it);

#define FOXDB_GET_TYPED_DEC(type, fname) type* fname(void* foxdb, const char* name)

FOXDB_GET_TYPED_DEC(foxdb_int_t, foxdb_get_int);
FOXDB_GET_TYPED_DEC(foxdb_bool_t, foxdb_get_bool);
FOXDB_GET_TYPED_DEC(foxdb_str_t, foxdb_get_str);

void foxdb_del_entry(foxdb_entry_t* entry);
foxdb_entry_t* foxdb_copy_entry(foxdb_entry_t* entry);

foxdb_int_t* foxdb_int(const char* name, int value);
foxdb_bool_t* foxdb_bool(const char* name, bool value);
foxdb_str_t* foxdb_str(const char* name, const char* value);
