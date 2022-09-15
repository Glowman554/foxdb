#include <command_manager.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
	create_command_manager(&command_manager);

	new_command(&command_manager, "help", "Shows help for a command!", help);

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