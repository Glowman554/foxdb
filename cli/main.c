#include <command_manager.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <foxdb.h>
#include <commands.h>

struct command_manager_t command_manager;

bool help_tr(slot_list_node_t* n) {
	struct command_t* cmd = n->data1;
	printf("%s -> %s\n", cmd->name, cmd->help);

	return true;
}

bool help(int argc, char** argv) {
	if (argc != 1) {
		printf("Command takes no arguments!\n");
		return false;
	}

	slot_list_transverse(&command_manager.command_list, help_tr);
	return true;
}

int main(int argc, char** argv) {
	switch (argc) {
		case 1:
			break;

		case 2:
			{
				FILE* f = fopen(argv[1], "rb");
				db = foxdb_from_file(f);
				fclose(f);

				printf("Loaded db from %s!\n", argv[1]);
			}
			break;

		default:
			printf("Usage: %s <db?>\n", argv[0]);
			return -1;
	}

	create_command_manager(&command_manager);

	new_command(&command_manager, "help", "Shows help for the commands!", help);

	new_command(&command_manager, "new_db", "Create a new db in memory!", new_db);
	new_command(&command_manager, "load_db", "Load a db from a file!", load_db);
	new_command(&command_manager, "save_db", "Save a db to a file", save_db);

	new_command(&command_manager, "keys", "List all keys in a db!", keys);
	new_command(&command_manager, "get", "Get the value from a key!", get);
	new_command(&command_manager, "remove", "Remove a key from the database!", remove_);

	new_command(&command_manager, "new_str", "Insert a new string into the database!", new_str);
	new_command(&command_manager, "new_int", "Insert a new int into the database!", new_int);
	new_command(&command_manager, "new_bool", "Insert a new bool into the database!", new_bool);

	new_command(&command_manager, "exit", "Self explanatory!", exit_);

	bool running = true;
	while (running) {
		char buf[128] = { 0 };

		printf("> ");
		fgets(buf, sizeof(buf), stdin);

		buf[strlen(buf) - 1] = 0; // remove trialing \n

		run_command(&command_manager, buf);
	}


	return 0;
}