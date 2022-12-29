//
// Created by potato_coder on 07.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H
#define SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H

#include <stdint-gcc.h>
#include "singly_linked_list.h"

typedef struct user_command {
    void (*name)(void *arg);

    void *arg;
    char *description;
} user_command;

void exit_command(void *arg);

void help_command(void *arg);

void tree_script_command(void *arg);

void k_command(void *arg);

void m_command(void *arg);

void n_command(void *arg);

void undefined_command(void *arg);

void run_command(user_command *command);

linked_list *commands_init();

void print_commands_help();

#endif //SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H
