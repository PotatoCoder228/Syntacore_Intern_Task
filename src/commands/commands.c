//
// Created by potato_coder on 07.12.22.
//

#include <stdio.h>
#include "../../include/commands.h"

linked_list *commands_init() {
    linked_list *commands_help_list;
    user_command *command_help = malloc(sizeof(user_command));
    command_help->name = HELP;
    command_help->description = "help - Выводит справку по командам";
    user_command *command_exit = malloc(sizeof(user_command));
    command_exit->name = EXIT;
    command_exit->description = "exit - Выход из приложения";

    user_command *command_tree_script = malloc(sizeof(user_command));
    command_tree_script->name = TREE_SCRIPT;
    command_tree_script->description = "tree_script <filename> - Выполнение скрипта, состоящего из ключей.";

    user_command *key_m = malloc(sizeof(user_command));
    key_m->name = M;
    key_m->description = "m <arg> - Запрос на поиск <arg>-го наименьшего элемента.";

    user_command *key_n = malloc(sizeof(user_command));
    key_n->name = N;
    key_n->description = "n <arg> - Поиск количества элементов, меньших, чем заданный i.";

    user_command *key_k = malloc(sizeof(user_command));
    key_k->name = K;
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

void print_commands_help(linked_list *commands_help_list) {
    printf("\nСправка по командам:\n");
    fflush_unlocked(stdout);
    while (commands_help_list != NULL) {
        fflush(stdout);
        printf("%s\n", ((user_command *) (commands_help_list->value))->description);
        commands_help_list = commands_help_list->next;
    }
}