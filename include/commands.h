//
// Created by potato_coder on 07.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H
#define SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H

#include <stdint-gcc.h>
#include "singly_linked_list.h"

typedef struct user_command {
    int64_t name;
    int64_t arg;
    char *description;
} user_command;

enum console_modes {
    READ_FROM_CONSOLE = 1001,
    READ_FROM_FILE = 1002
};

enum users_commands {
    K = 2001,
    M = 2002,
    N = 2003,
    EXIT = 2004,
    HELP = 2005,
    TREE_SCRIPT = 2006
};

linked_list *commands_init();

void print_commands_help(linked_list *commands_help_list);

#endif //SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H
