#include <stdio.h>
#include <assert.h>
#include <foxdb.h>

int main() {
	void* db = foxdb_new();

	foxdb_int_t* i = foxdb_int("test_int", 100);
	foxdb_bool_t* b = foxdb_bool("test_bool", true);
	foxdb_str_t* s = foxdb_str("test_str", "hewoo from a string!");

	db = foxdb_insert(db, (foxdb_entry_t*) i);
	db = foxdb_insert(db, (foxdb_entry_t*) b);
	db = foxdb_insert(db, (foxdb_entry_t*) s);
	
	foxdb_del_entry((foxdb_entry_t*) i);
	foxdb_del_entry((foxdb_entry_t*) b);
	foxdb_del_entry((foxdb_entry_t*) s);

	i = (foxdb_int_t*) foxdb_get(db, "test_int");
	assert(i->header.type == FOXDB_INT);
	printf("%d\n", i->val);
	b = (foxdb_bool_t*) foxdb_get(db, "test_bool");
	assert(b->header.type == FOXDB_BOOL);
	printf("%s\n", b->val ? "true" : "false");
	s = (foxdb_str_t*) foxdb_get(db, "test_str");
	assert(s->header.type == FOXDB_STR);
	printf("%s\n", s->val);

	foxdb_del_entry((foxdb_entry_t*) i);
	foxdb_del_entry((foxdb_entry_t*) b);
	foxdb_del_entry((foxdb_entry_t*) s);

	foxdb_del(db);

	return 0;
}