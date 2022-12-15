//
// Created by potato_coder on 04.12.22.
//

#include <stdint-gcc.h>
#include <stdio.h>
#include "../../include/io_stream_handler.h"
#include "../../include/commands.h"

int read_command(char *buffer, size_t string_size) {
    size_t counter = 0;
    char character = getchar();
    while (character != EOF && character != '\n' && character != '\0') {
        if (counter >= string_size) {
            character = getchar();
            continue;
        }
        buffer[counter] = character;
        counter++;
        character = getchar();
    }
    rewind(stdin);
    return 0;
}

int console_start() {
    int8_t is_work = 1;
    printf("\nДобро пожаловать в консольное приложение!\n");
    linked_list *commands_help_list = commands_init();
    print_commands_help(commands_help_list);

    while (is_work) {
        printf("\nВведите команды и ключи:");
        char *string[5] = {0};
        read_command(string, 5);
        printf("%s", string);
    }
    return 0;
}