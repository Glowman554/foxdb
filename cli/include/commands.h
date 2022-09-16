#pragma once

#include <stdbool.h>

bool new_db(int argc, char** argv);
bool load_db(int argc, char** argv);
bool save_db(int argc, char** argv);

bool keys(int argc, char** argv);
bool get(int argc, char** argv);

bool new_str(int argc, char** argv);
