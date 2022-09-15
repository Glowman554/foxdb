/*
-------------------------- notice --------------------------
| This code is from https://github.com/Glowman554/command  |
------------------------------------------------------------
*/

#include <command_manager.h>
#include <argv_splitter.h>
#include <argv_count.h>
#include <stdlib.h>
#include <string.h>

void create_command_manager(struct command_manager_t* cmd) {
	slot_list_create(&cmd->command_list);
}

void dispose_enumeration(slot_list_node_t* node) {
	free(node->data1);
}

void dispose_command_manager(struct command_manager_t* cmd) {
	slot_list_transverse(&cmd->command_list, (slot_transverse_function) dispose_enumeration);
	slot_list_dispose(&cmd->command_list);
}

void new_command(struct command_manager_t* cmd, char* name, char* help, command_executor executor) {
	struct command_t* command = (struct command_t*) malloc(sizeof(struct command_t));

	strcpy(command->name, name);
	strcpy(command->help, help);

	command->executor = executor;

	slot_list_add_node(&cmd->command_list, command, NULL, NULL, NULL);
}

bool search_command(slot_list_node_t* node, void* d1, void* d2, void* d3, void* d4) {
	if(strcmp(((struct command_t*) node->data1)->name, d1) == 0) {
		return true;
	} else {
		return false;
	}
}

bool run_command(struct command_manager_t* cmd, char* message) {
	char* tmp = (char*) malloc(sizeof(char) * strlen(message));
	strcpy(tmp, message);

	char** arguments = argv_split(tmp);

	slot_list_node_t* command_found = slot_list_find_node(&cmd->command_list, search_command, arguments[0], NULL, NULL, NULL);

	if(command_found == NULL) {
		return false;
	}

	struct command_t* final_command = (struct command_t*) command_found->data1;

	final_command->executor(argv_count(arguments), arguments);

	free(arguments);
	free(tmp);

	return true;
}