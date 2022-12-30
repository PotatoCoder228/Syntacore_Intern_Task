//
// Created by potato_coder on 07.12.22.
//

#include <stdio.h>
#include "stdlib.h"
#include "../../include/commands.h"

extern linked_list *commands_help_list;
extern int8_t is_working;

typedef struct user_command {
    void (*callback)(void *arg);

    void *arg;
    char *description;
} user_command;

user_command *new_user_command(void callback(void *), void *arg, char *descr) {
    user_command *command = malloc(sizeof(user_command));
    command->callback = callback;
    command->arg = arg;
    command->description = descr;
    return command;
}

void *user_command_get_callback(user_command *command) {
    return command->callback;
}

void user_command_set_callback(user_command *command, void callback(void *)) {
    command->callback = callback;
}

void *user_command_get_arg(user_command *command) {
    return command->arg;
}

void user_command_set_arg(user_command *command, void *arg) {
    command->arg = arg;
}

char *user_command_get_description(user_command *command) {
    return command->description;
}

void user_command_set_description(user_command *command, char *description) {
    command->description = description;
}

void user_command_destroy(user_command *command) {
    free(command);
}

void run_command(user_command *command) {
    void (*command_call)(void *arg) = command->callback;
    command_call(command->arg);
}

void exit_command(void *arg) {
    is_working = 0;
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
    printf("%s%s", "\nНекорректная команда, попробуйте ввести ещё раз!\n", "help - справка по командам\n");
}

linked_list *commands_init() {
    user_command *command_help = new_user_command(help_command, NULL, (void *) descriptions[HELP]);
    user_command *command_exit = new_user_command(exit_command, NULL, (void *) descriptions[EXIT]);
    user_command *command_tree_script = new_user_command(tree_script_command, NULL, (void *) descriptions[TREE_SCRIPT]);
    user_command *key_m = new_user_command(m_command, NULL, (void *) descriptions[M]);
    user_command *key_n = new_user_command(n_command, NULL, (void *) descriptions[N]);
    user_command *key_k = new_user_command(k_command, NULL, (void *) descriptions[K]);

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
        printf("%s\n", ((user_command *) linked_list_get_node_value(buffer))->description);
        buffer = linked_list_get_node_next(buffer);
    }
}