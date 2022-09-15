#include <stdio.h>
#include <assert.h>
#include <foxdb.h>

int main() {
	void* db = foxdb_new();

	foxdb_int_t* i = foxdb_int("test_int", 100);
	foxdb_bool_t* b = foxdb_bool("test_bool", true);

	db = foxdb_insert(db, (foxdb_entry_t*) i);
	db = foxdb_insert(db, (foxdb_entry_t*) b);

	foxdb_del_entry((foxdb_entry_t*) i);
	foxdb_del_entry((foxdb_entry_t*) b);

	i = (foxdb_int_t*) foxdb_get(db, "test_int");
	assert(i->header.type == FOXDB_INT);
	printf("%d\n", i->val);
	b = (foxdb_bool_t*) foxdb_get(db, "test_bool");
	assert(b->header.type == FOXDB_BOOL);
	printf("%s\n", b->val ? "true" : "false");

	foxdb_del_entry((foxdb_entry_t*) i);
	foxdb_del_entry((foxdb_entry_t*) b);

	foxdb_del(db);

	return 0;
}