//
// Created by potato_coder on 04.12.22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/io_stream_handler.h"
#include "../../include/commands.h"

extern int8_t is_work;

void set_command_name(user_command *command, char *string) {
    if (strcmp(string, "help") == 0) {
        command->name = help_command;
    } else if (strcmp(string, "exit") == 0) {
        command->name = exit_command;
    } else if (strcmp(string, "tree_script") == 0) {
        command->name = tree_script_command;
    } else if (strcmp(string, "k") == 0) {
        command->name = k_command;
    } else if (strcmp(string, "m") == 0) {
        command->name = m_command;
    } else if (strcmp(string, "n") == 0) {
        command->name = n_command;
    } else {
        command->name = undefined_command;
    }
}

char **get_command(linked_list *string) {//OK
    char *command = NULL;
    char *arg = NULL;
    char **command_and_arg = malloc(sizeof(char *) * 2);
    command_and_arg[0] = NULL;
    command_and_arg[1] = NULL;
    linked_list *buf = string;
    size_t list_size = linked_list_get_size(string);
    size_t command_length = 0;
    size_t arg_length = 0;
    while (string != NULL) {
        if (((char *) (string->value))[0] == 32 || ((char *) (string->value))[0] == '\n' ||
            ((char *) (string->value))[0] == EOF || ((char *) (string->value))[0] == '\t') {
            break;
        }
        string = string->next;
        command_length++;
    }
    command = malloc(sizeof(char) * command_length);
    for (size_t i = 0; i < command_length; i++) {
        command[i] = ((char *) linked_list_get(buf, i))[0];
    }
    command[command_length] = '\0';
    command_and_arg[0] = command;
    arg_length = list_size - command_length - 1;
    arg = malloc(sizeof(char) * (arg_length));
    for (size_t i = 0; i < arg_length; i++) {
        arg[i] = ((char *) (string->value))[0];
        string = string->next;
    }
    command_and_arg[1] = arg;
    return command_and_arg;
}

void parse_command(user_command *command_struct, linked_list *user_input) {
    char **command_and_arg = get_command(user_input);
    int64_t arg;
    char *end;
    arg = strtol(command_and_arg[1], &end, 10);
    if (arg != '\0') {
        int64_t *arg_ptr = malloc(sizeof(int64_t));
        arg_ptr[0] = arg;
        command_struct->arg = arg_ptr;
    } else {
        char *arg_ptr = malloc(sizeof(command_and_arg[1]));
        for (size_t i = 0; i < sizeof(command_and_arg[1]); i++) {
            arg_ptr[i] = command_and_arg[1][i];
        }
        command_struct->arg = arg_ptr;
    }
    set_command_name(command_struct, command_and_arg[0]);
    free(command_and_arg[0]);
    free(command_and_arg[1]);
    free(command_and_arg);
}

linked_list *read_command() {
    rewind(stdin);
    char *character = malloc(sizeof(char) * 2);
    linked_list *string_buffer;
    size_t counter = 0;
    character[0] = getchar();
    character[1] = '\0';
    while (character[0] != EOF && character[0] != '\n' && character[0] != '\0') {
        if (counter == 0) {
            counter++;
            string_buffer = linked_list_init(character);
            character = malloc(sizeof(char) * 2);
            character[0] = getchar();
            character[1] = '\0';
            continue;
        }
        linked_list_push(string_buffer, character);
        character = malloc(sizeof(char) * 2);
        character[0] = getchar();
        character[1] = '\0';
    }
    rewind(stdin);
    return string_buffer;
}

int console_start() {
    is_work = 1;
    printf("\nДобро пожаловать в консольное приложение!\n");
    commands_init();
    print_commands_help();

    /**
     * Идея: все команды читаются по очереди, помещаются в буфер,
     * потом вызывается метод, парсящий команду и образующий структуру команды,
     * если что-то не так, то возвращается enum с ошибкой и ошибка выводится пользователю
     * (отсутствие аргумента, неверная команда, аргумент - не число) и просьба ввести команду ещё раз
    */
    fflush_unlocked(stdout);
    linked_list *char_list;
    user_command *command = malloc(sizeof(user_command));
    while (is_work) {
        printf("\nВведите команду:");
        char_list = read_command();
        parse_command(command, char_list);
        run_command(command);
        linked_list_destroy(char_list, 1);
        char_list = NULL;
    }
    return 0;
}