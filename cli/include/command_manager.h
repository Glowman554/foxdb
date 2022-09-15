#pragma once

/*
-------------------------- notice --------------------------
| This code is from https://github.com/Glowman554/command  |
------------------------------------------------------------
*/

#include <slot_list.h>

typedef bool (*command_executor)(int argc, char** argv);

struct command_manager_t {
	slot_list_t command_list;
};

struct command_t {
	char name[16];
	char help[1024];
	command_executor executor;
};


bool run_command(struct command_manager_t* cmd, char* message);
void new_command(struct command_manager_t* cmd, char* name, char* help, command_executor executor);

void create_command_manager(struct command_manager_t* cmd);
void dispose_command_manager(struct command_manager_t* cmd);