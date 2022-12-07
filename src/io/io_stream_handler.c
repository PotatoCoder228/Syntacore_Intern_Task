//
// Created by potato_coder on 04.12.22.
//

#include <stdint-gcc.h>
#include <stdio.h>
#include "../../include/io_stream_handler.h"

int read_command(char* buffer, size_t string_size){
    size_t counter = 0;
    char character = getchar();
    while(character != EOF && character != '\n' && character != '\0'){
        if(counter >= string_size){
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

int call_main_console(){
    int8_t is_work = 1;
    while(is_work){
        char* string[5] = {0};
        printf("\nПриветствую, мастер Йода!\n");
        read_command(string, 5);
        printf("%s", string);
    }
    return 0;
}