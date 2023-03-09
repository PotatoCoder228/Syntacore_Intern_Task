//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_COMMAND_H
#define SYNTACORE_TOOLS_INTERN_TASK_COMMAND_H

#include <stdlib.h>
#include <stdint.h>
#include "../exceptions/error_s.h"
#include "../containers/list_s.h"
#include "../containers/containers.h"

enum command_consts {
    DESCR_LEN = 10
};

static const char *descriptions[DESCR_LEN] = {
        "help - Выводит справку по командам;",
        "script - Выполнение скрипта, состоящего из ключей.",
        "m <arg> - Ключ на поиск <arg>-го наименьшего элемента.",
        "n <arg> - Ключ на поиск количества элементов, меньших, чем заданный i.",
        "k <arg> - Ключ на вставку уникального числа в дерево.",
        "d <arg> - Ключ на удаление числа из дерева",
        "clear - Очистить дерево",
        "print - Распечатать дерево",
        "exit - Выход из приложения;",
        "Вводить ключи можно в одну строчку."
};

typedef struct user_command user_command;

user_command *new_user_command(void callback(user_command *, error_s *), void *arg);

void *user_command_callback(user_command *command);

void user_command_set_callback(user_command *command, void callback(user_command *, error_s *));

void *user_command_arg(user_command *command);

void user_command_set_arg(user_command *command, void *arg);

char *user_command_get_description(user_command *command);

void user_command_set_description(user_command *command, char *description);

void user_command_destroy(void *command);

void print_command(user_command *command, error_s *error);

void run_command(user_command *command, error_s *error);

void k_command(user_command *command, error_s *error);

void n_command(user_command *command, error_s *error);

void m_command(user_command *command, error_s *error);

void d_command(user_command *command, error_s *error);

void clear_command(user_command *command, error_s *error);

void script_command(user_command *command, error_s *error);

void undefined_command(user_command *command, error_s *error);

void help_command(user_command *command, error_s *error);

void exit_command(user_command *command, error_s *error);

int command_char_arg_compare(void *com1, void *com2);

int user_command_print(FILE *stream, char *mode, void *command);

#endif //SYNTACORE_TOOLS_INTERN_TASK_COMMAND_H
