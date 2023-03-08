//
// Created by sasha on 04.03.2023.
//

#include "../../include/console/console.h"
#include "../../include/containers/containers.h"

rb_tree_s *commands_tree = NULL;

string_builder *read_line(FILE *stream, error_s *error) {
    if (stream == NULL) {
        throw_exception(error, NULL_PTR_ERROR, "read_line: передан NULL указатель на FILE*.");
        return NULL;
    }
    string_builder *line = new_string_builder();
    string_builder *buffer = new_string_builder();
    char *character = malloc(sizeof(char) * 2);
    if (character == NULL || line == NULL) {
        throw_exception(error, MEM_ALLOC_DENIED, "read_line: недостаточно памяти.");
        string_builder_destroy(line);
        string_builder_destroy(buffer);
        return NULL;
    }
    character[0] = fgetc(stream);
    character[1] = '\0';
    while (character[0] == EOF && stream == stdin) {
        printf("%s", "\nНекорректный ввод, попробуйте ввести ещё раз:");
        clearerr(stdin);
        character[0] = fgetc(stream);
    }
    while (character[0] != '\0' && character[0] != '\n' && feof(stream) == 0) {
        string_builder_set_string(buffer, character);
        if (string_builder_concat(line, buffer)) {
            character[0] = fgetc(stream);
        } else {
            throw_exception(error, MEM_ALLOC_DENIED, "read_line: недостаточно памяти для выделения.");
        }
    }
    string_builder_destroy(buffer);
    free(character);
    character = NULL;
    return line;
}

user_command *get_user_command_from_vector(vector_s *tokens) {
    user_command *command = new_user_command(NULL, NULL);
    string_builder *name = (string_builder *) vector_get(tokens, 0);
    if (vector_get_size(tokens) == 1) {
        if (!strcmp(string_builder_get_string(name), "help")) {
            user_command_set_callback(command, help_command);
        } else if (!strcmp(string_builder_get_string(name), "exit")) {
            user_command_set_callback(command, exit_command);
        } else if (!strcmp(string_builder_get_string(name), "script")) {
            user_command_set_callback(command, script_command);
        } else if (!strcmp(string_builder_get_string(name), "clear")) {
            user_command_set_callback(command, clear_command);
        } else if (!strcmp(string_builder_get_string(name), "print")) {
            user_command_set_callback(command, print_command);
        } else {
            user_command_set_callback(command, undefined_command);
        }
        return command;
    }

    if (!strcmp(string_builder_get_string(name), "n")) {
        user_command_set_callback(command, n_command);
    } else if (!strcmp(string_builder_get_string(name), "m")) {
        user_command_set_callback(command, m_command);
    } else if (!strcmp(string_builder_get_string(name), "k")) {
        user_command_set_callback(command, k_command);
    } else if (!strcmp(string_builder_get_string(name), "d")) {
        user_command_set_callback(command, d_command);
    } else {
        user_command_set_callback(command, undefined_command);
        return command;
    }
    user_command_set_arg(command, vector_get(tokens, 1));
    return command;
}

user_command *parse_and_set_tree_command(vector_s *vector, size_t index) {
    if (index < vector_get_size(vector)) {
        string_builder *name = (string_builder *) vector_get(vector, index);
        user_command *command;
        if (!strcmp(string_builder_get_string(name), "n")) {
            command = new_user_command(NULL, NULL);
            user_command_set_callback(command, n_command);
        } else if (!strcmp(string_builder_get_string(name), "m")) {
            command = new_user_command(NULL, NULL);
            user_command_set_callback(command, m_command);
        } else if (!strcmp(string_builder_get_string(name), "k")) {
            command = new_user_command(NULL, NULL);
            user_command_set_callback(command, k_command);
        } else if (!strcmp(string_builder_get_string(name), "d")) {
            command = new_user_command(NULL, NULL);
            user_command_set_callback(command, d_command);
        } else {
            command = NULL;
            return command;
        }
        user_command_set_arg(command, vector_get(vector, index + 1));
        return command;
    }
    return NULL;
}

bool console(error_s *error) {
    while (true) {
        printf("%s", "\nВведите команду:");
        string_builder *line = read_line(stdin, error);
        if (line == NULL) {
            throw_exception(error, MEM_ALLOC_DENIED, "console(): недостаточно памяти для работы приложения.\n");
            return false;
        }
        vector_s *tokens_vector = string_builder_get_tokens(line, " \t\r");
        if (tokens_vector == NULL || vector_get(tokens_vector, 0) == NULL) {
            printf("Вы не ввели команду. Попробуйте снова.\n");
            string_builder_destroy(line);
            continue;
        } else if (vector_get_size(tokens_vector) < 3) {
            user_command *command = get_user_command_from_vector(tokens_vector);
            if (user_command_get_callback(command) == exit_command) {
                run_command(command, error);
                vector_destroy(tokens_vector, string_builder_destroy);
                string_builder_destroy(line);
                break;
            } else if (user_command_get_callback(command) == k_command) {
                if (rb_is_empty(commands_tree)) {
                    commands_tree = new_rb_tree(command);
                    run_command(command, error);
                } else {
                    rb_tree_s *buf = rb_search(commands_tree, command, command_char_arg_compare);
                    if (rb_is_empty(buf)) {
                        rb_insert(&commands_tree, new_rb_node(command), command_char_arg_compare);
                        run_command(command, error);
                    } else {
                        printf("Такое число уже есть в дереве.\n");
                    }
                }
            } else {
                run_command(command, error);
            }
            string_builder_destroy(line);
        } else {
            if (vector_get_size(tokens_vector) % 2 != 0) {
                printf("Число команд не соответствует числу аргументов\n");
            } else {
                vector_s *coms = new_vector();
                for (size_t i = 0; i < vector_get_size(tokens_vector); i += 2) {
                    user_command *command = parse_and_set_tree_command(tokens_vector, i);
                    if (command == NULL) {
                        printf("Некорректная команда.\n");
                        user_command_destroy(command);
                        break;
                    }
                    if (user_command_get_callback(command) == k_command) {
                        object_s key = command;
                        rb_tree_s *buf = rb_search(commands_tree, key, command_char_arg_compare);
                        if (rb_is_empty(buf)) {
                            if (rb_is_empty(commands_tree)) {
                                commands_tree = new_rb_tree(key);
                            } else {
                                rb_insert(&commands_tree, new_rb_node(key), command_char_arg_compare);
                            }
                            vector_push(coms, key);
                        } else {
                            printf("В последовательности команд было несколько k c одинаковыми аргументами.\n");
                            printf("Либо какое-то из чисел уже есть в дереве.\n");
                            break;
                        }
                    } else {
                        object_s key = command;
                        vector_push(coms, key);
                    }
                }
                if (!rb_is_empty(commands_tree)) {
                    for (size_t j = 0; j < vector_get_size(coms); j++) {
                        run_command(vector_get(coms, j), error);
                    }
                } else {
                    for (size_t j = 0; j < vector_get_size(coms); j++) {
                        rb_tree_s *node = rb_search(commands_tree, vector_get(coms, j), command_char_arg_compare);
                        rb_delete(&commands_tree, node);
                        user_command_destroy(vector_get(coms, j));
                    }
                }
            }
            for (size_t i = 0; i < vector_get_size(tokens_vector); i += 2) {
                user_command *command = vector_get(tokens_vector, i);
                if (user_command_get_callback(command) != k_command) {
                    user_command_destroy(command);
                }
            }
            free(tokens_vector);
            string_builder_destroy(line);
        }
    }
    rb_foreach_free(commands_tree, user_command_destroy);
    rb_destroy(commands_tree);
    commands_tree = NULL;
    return true;
}