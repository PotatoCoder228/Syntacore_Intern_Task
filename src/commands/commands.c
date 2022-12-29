//
// Created by potato_coder on 07.12.22.
//

#include <stdio.h>
#include "../../include/commands.h"

extern linked_list *commands_help_list;
extern int8_t is_work;

void run_command(user_command *command) {
    void (*command_call)(void *arg) = command->name;
    command_call(command->arg);
}

void exit_command(void *arg) {
    is_work = 0;
    //command_list_destroy();
}

void help_command(void *arg) {
    print_commands_help();
}

void tree_script_command(void *arg) {

}

void k_command(void *arg) {

}

void m_command(void *arg) {

}

void n_command(void *arg) {

}

void undefined_command(void *arg) {
    printf("\nНекорректная команда, попробуйте ввести ещё раз!\n");
    printf("help - справка по командам\n");
}

linked_list *commands_init() {
    user_command *command_help = malloc(sizeof(user_command));
    command_help->name = help_command;
    command_help->description = "help - Выводит справку по командам";
    user_command *command_exit = malloc(sizeof(user_command));
    command_exit->name = exit_command;
    command_exit->description = "exit - Выход из приложения";

    user_command *command_tree_script = malloc(sizeof(user_command));
    command_tree_script->name = tree_script_command;
    command_tree_script->description = "tree_script <filename> - Выполнение скрипта, состоящего из ключей.";

    user_command *key_m = malloc(sizeof(user_command));
    key_m->name = m_command;
    key_m->description = "m <arg> - Запрос на поиск <arg>-го наименьшего элемента.";

    user_command *key_n = malloc(sizeof(user_command));
    key_n->name = n_command;
    key_n->description = "n <arg> - Поиск количества элементов, меньших, чем заданный i.";

    user_command *key_k = malloc(sizeof(user_command));
    key_k->name = k_command;
    key_k->description = "k <arg> - Вставка уникального ключа в дерево.";
    commands_help_list = linked_list_init(command_help);
    linked_list_push(commands_help_list, command_exit);
    linked_list_push(commands_help_list, command_tree_script);
    linked_list_push(commands_help_list, key_k);
    linked_list_push(commands_help_list, key_m);
    linked_list_push(commands_help_list, key_n);
    linked_list_push(commands_help_list, command_exit);
    return commands_help_list;
}

void print_commands_help() {
    linked_list *buffer = commands_help_list;
    printf("\nСправка по командам:\n");
    while (buffer != NULL) {
        fflush(stdout);
        printf("%s\n", ((user_command *) (buffer->value))->description);
        buffer = buffer->next;
    }
}