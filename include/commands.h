//
// Created by potato_coder on 07.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H
#define SYNTACORE_TOOLS_INTERN_TASK_COMMANDS_H

#include <stdint.h>
#include "singly_linked_list.h"

enum commands {
    HELP = 0,
    EXIT,
    TREE_SCRIPT,
    M,
    N,
    K
};

static const char *descriptions[6] = {
        "help - Выводит справку по командам",
        "exit - Выход из приложения",
        "tree_script <filename> - Выполнение скрипта, состоящего из ключей.",
        "m <arg> - Запрос на поиск <arg>-го наименьшего элемента.",
        "n <arg> - Поиск количества элементов, меньших, чем заданный i.",
        "k <arg> - Вставка уникального ключа в дерево."
};

typedef struct user_command user_command;

user_command *new_user_command(void callback(void *), void *arg, char *descr);

void *user_command_get_callback(user_command *command);

void user_command_set_callback(user_command *command, void callback(void *));

void *user_command_get_arg(user_command *command);

void user_command_set_arg(user_command *command, void *arg);

char *user_command_get_description(user_command *command);

void user_command_set_description(user_command *command, char *description);

void user_command_destroy(user_command *command);

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
