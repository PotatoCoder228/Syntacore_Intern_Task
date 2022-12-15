//
// Created by potato_coder on 04.12.22.
//

#include <stdint-gcc.h>
#include <stdio.h>
#include <string.h>
#include "../../include/io_stream_handler.h"
#include "../../include/commands.h"
/*
char* get_command_arg(char* string, size_t buffer_size, size_t command_end){
    char* command = NULL;
    for(size_t i = 0; i < buffer_size; i++){
    return command;
}
 */

//TODO переделать для работы с linked_list
char *get_command(char *string, size_t buffer_size) {//OK
    char *command = NULL;
    size_t command_length = 0;
    for (size_t i = 0; i < buffer_size; i++) {
        if (string[i] == 32 || string[i] == '\n' || string[i] == EOF || string[i] == '\t') {
            break;
        }
        command_length++;
    }
    command = malloc(sizeof(char) * command_length);
    for (size_t i = 0; i < command_length; i++) {
        command[i] = string[i];
    }
    command[command_length] = '\0';
    return command;
}

int parse_command(user_command *buffer, char *string) {

}

linked_list *read_command() {
    char *character = malloc(sizeof(char));
    linked_list *string_buffer;
    size_t counter = 0;
    character[0] = getchar();
    while (character[0] != EOF && character[0] != '\n' && character[0] != '\0') {
        if (counter == 0) {
            counter++;
            string_buffer = linked_list_init(character);
            character = malloc(sizeof(char));
            character[0] = getchar();
            continue;
        }
        linked_list_push(string_buffer, character);
        character = malloc(sizeof(char));
        character[0] = getchar();
    }
    rewind(stdin);
    return string_buffer;
}

int console_start() {
    int8_t is_work = 1;
    printf("\nДобро пожаловать в консольное приложение!\n");
    linked_list *commands_help_list = commands_init();
    print_commands_help(commands_help_list);

    /**
     * Идея: все команды читаются по очереди, помещаются в буфер,
     * потом вызывается метод, парсящий команду и образующий структуру команды,
     * если что-то не так, то возвращается enum с ошибкой и ошибка выводится пользователю
     * (отсутствие аргумента, неверная команда, аргумент - не число) и просьба ввести команду ещё раз
    */

    while (is_work) {
        printf("\nВведите команду:");
        linked_list *char_list = read_command();
        print_linked_list(stdout, "%s", char_list);
        //printf("%s\n", string);
        //char* command = get_command(string, command_buffer_size);

    }
    return 0;
}