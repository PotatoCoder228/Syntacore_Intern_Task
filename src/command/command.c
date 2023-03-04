//
// Created by sasha on 04.03.2023.
//

#include "../../include/command/command.h"

typedef struct user_command {
    void (*callback)(error_s *error);

    void *arg;
} user_command;

user_command *new_user_command(void callback(error_s *), char *arg) {
    user_command *command = malloc(sizeof(user_command));
    if (command != NULL) {
        command->callback = callback;
        command->arg = arg;
    }
    return command;
}

void *user_command_get_callback(user_command *command) {
    if (command != NULL) {
        return command->callback;
    }
    return NULL;
}

void user_command_set_callback(user_command *command, void callback(error_s *)) {
    if (command != NULL) {
        command->callback = callback;
    }
}

void *user_command_get_arg(user_command *command) {
    if (command != NULL) {
        return command->arg;
    }
    return NULL;
}

void user_command_set_arg(user_command *command, void *arg) {
    if (command != NULL) {
        command->arg = arg;
    }
}

void user_command_destroy(void *command) {
    if (command != NULL) {
        free(command);
    }
}

void help_command(error_s *error) {
    printf("\nСправка по командам:\n");
    for (int i = 0; i < DESCR_LEN; i++) {
        printf("%s\n", descriptions[i]);
    }
}

void k_command(error_s *error) {

}

void n_command(error_s *error) {

}

void script_command(error_s *error) {

}

void m_command(error_s *error) {

}

void exit_command(error_s *error) {
    printf("%s\n", "Производится выход из программы...");
}

void undefined_command(error_s *error) {
    printf("%s%s", "\nНекорректная команда, попробуйте ввести ещё раз!\n", "help - справка по командам\n");
}

void run_command(user_command *command, error_s *error) {
    if (command != NULL) {
        void (*command_call)(error_s *) = command->callback;
        command_call(error);
        return;
    }
    throw_exception(error, NULL_PTR_ERROR, "run_command: передан NULL указатель на command.");
}

int command_char_arg_compare(void *com1, void *com2) {
    if (com1 != NULL && com2 != NULL) {
        return string_builder_equals((((user_command *) com1)->arg), (((user_command *) com2)->arg));
    }
    return 0;
}

char *user_command_to_string(void *command) {
    return string_builder_to_string((((user_command *) command)->arg));
}