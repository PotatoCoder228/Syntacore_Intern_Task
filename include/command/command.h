//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_COMMAND_H
#define SYNTACORE_TOOLS_INTERN_TASK_COMMAND_H

#include <stdlib.h>
#include <stdint.h>
#include "../exceptions/error_s.h"
#include "../containers/list_s.h"

enum command {
    HELP = 0,
    EXIT,
    K,
    M,
    N
};

enum command_consts {
    DESCR_LEN = 7
};

static const char *descriptions[DESCR_LEN] = {
        "help - Выводит справку по командам;",
        "script <filename> - Выполнение скрипта, состоящего из ключей.",
        "m <arg> - Запрос на поиск <arg>-го наименьшего элемента.",
        "n <arg> - Поиск количества элементов, меньших, чем заданный i.",
        "k <arg> - Вставка уникального ключа в дерево.",
        "exit - Выход из приложения;",
        "Вводить ключи можно в одну строчку."
};

typedef struct user_command user_command;

user_command *new_user_command(void callback(error_s *), char *arg);

void *user_command_get_callback(user_command *command);

void user_command_set_callback(user_command *command, void callback(error_s *));

void *user_command_get_arg(user_command *command);

void user_command_set_arg(user_command *command, void *arg);

char *user_command_get_description(user_command *command);

void user_command_set_description(user_command *command, char *description);

void user_command_destroy(void *command);

void run_command(user_command *command, error_s *error);

void k_command(error_s *error);

void n_command(error_s *error);

void m_command(error_s *error);

void script_command(error_s *error);

void undefined_command(error_s *error);

void help_command(error_s *error);

void exit_command(error_s *error);

int command_char_arg_compare(void *com1, void *com2);

char *user_command_to_string(void *command);

#endif //SYNTACORE_TOOLS_INTERN_TASK_COMMAND_H
