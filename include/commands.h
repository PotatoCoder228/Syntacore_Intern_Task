//
// Created by potato_coder on 07.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H
#define SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H

#include <stdint-gcc.h>

struct user_command{
    int64_t name;
    int64_t arg;
    char* decription;
}user_command;

enum console_modes{
    READ_FROM_CONSOLE = 1001,
    READ_FROM_FILE = 1002
};

enum users_commands{
    K = 2001,
    M = 2002,
    N = 2003,
    EXIT = 2004,
    HELP = 2005,
    TREE_SCRIPT = 2006
};

void print_commands_help();

#endif //SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H
