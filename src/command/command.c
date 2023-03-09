//
// Created by sasha on 04.03.2023.
//

#include "../../include/command/command.h"
#include "../../include/app.h"
#include "../../include/console/console.h"
#include "../../include/io/io_handler.h"

extern rb_tree_s *commands_tree;

typedef struct user_command {
    void (*callback)(user_command *command, error_s *error);

    void *arg;
} user_command;

user_command *new_user_command(void callback(user_command *, error_s *), void *arg) {
    user_command *command = malloc(sizeof(user_command));
    if (command != NULL) {
        command->callback = callback;
        command->arg = arg;
    }
    return command;
}

void *user_command_callback(user_command *command) {
    if (command != NULL) {
        return command->callback;
    }
    return NULL;
}

void user_command_set_callback(user_command *command, void callback(user_command *, error_s *)) {
    if (command != NULL) {
        command->callback = callback;
    }
}

void *user_command_arg(user_command *command) {
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

void help_command(user_command *command, error_s *error) {
    printf("\nСправка по командам:\n");
    for (int i = 0; i < DESCR_LEN; i++) {
        printf("%s\n", descriptions[i]);
    }
}

void k_command(user_command *command, error_s *error) {
    if (command != NULL) {
        char *end = NULL;
        int64_t key = strtol(string_builder_get_string(command->arg), &end, 10);
        if (end != NULL && end[0] != 0) {
            printf("Некорректное значение аргумента для ключа.\n");
            return;
        }
        if (!global_tree_is_init()) {
            global_tree_init(key);
        } else {
            global_tree_insert(key);
        }
        printf("Число %ld успешно вставлено.\n", key);
    } else {
        throw_exception(error, NULL_PTR_ERROR, "k_command: передан NULL указатель.");
    }
}

void n_command(user_command *command, error_s *error) {
    if (command != NULL) {
        char *end = NULL;
        int64_t key = strtol(string_builder_get_string(command->arg), &end, 10);
        if (end != NULL && end[0] != 0) {
            printf("Некорректное значение аргумента для ключа.\n");
            return;
        }
        if (global_tree_is_init()) {
            printf("Количество чисел, меньших, чем %ld: %zu\n", key, global_tree_counts_less_than(key));
        } else {
            printf("Дерево не инициализировано. Элементы отсутствуют.\n");
        }
    } else {
        throw_exception(error, NULL_PTR_ERROR, "n_command: передан NULL указатель.");
    }
}

static void write_test_answer(error_s *error) {
    FILE *file = open_file("tree_values.txt", W, error);
    if (file != NULL) {
        global_tree_inorder_print(file);
        for (int i = 1; i < global_tree_get_size(); i++) {
            fprintf(file, "%ld ", global_tree_k_stat(i));
        }
        for (int i = 0; i < global_tree_get_size(); i++) {
            fprintf(file, "%ld ", global_tree_counts_less_than(i));
        }
        fclose(file);
    }
}

void script_command(user_command *command, error_s *error) {
    error_set_default(error);
    printf("Введите имя файла:");
    string_builder *arg = read_line(stdin, error);
    if (arg == NULL) {
        throw_exception(error, INPUT_STREAM_READ_ERROR, "script command: Не удалось прочитать строку.");
    }
    FILE *file = open_file(string_builder_get_string(arg), R, error);
    if (file == NULL) {
        string_builder_destroy(arg);
        printf("Не удалось открыть файл...\n");
        return;
    }
    printf("Идёт выполнение из файла...\n");

    while (true) {
        string_builder *file_line = read_line(file, error);
        vector_s *tokens = string_builder_get_tokens(file_line, " \t\r");
        if (tokens == NULL || vector_get(tokens, 0) == NULL) {
            string_builder_destroy(file_line);
            break;
        }
        vector_s *coms = new_vector();
        for (size_t i = 0; i < vector_size(tokens); i += 2) {
            user_command *com = parse_and_set_tree_command(tokens, i);
            if (com == NULL) {
                printf("Некорректная команда.\n");
                rb_foreach_free(commands_tree, user_command_destroy);
                rb_destroy(commands_tree);
                commands_tree = NULL;
                break;
            }
            if (user_command_callback(com) == k_command) {
                object_s *key = (void *) com;
                //rb_tree_print(commands_tree, user_command_to_string,0);
                rb_tree_s *buf = rb_search(commands_tree, key, command_char_arg_compare);
                if (rb_is_empty(buf)) {
                    if (commands_tree == NULL) {
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
                object_s *key = (void *) com;
                vector_push(coms, key);
            }
        }
        if (commands_tree != NULL) {
            for (size_t j = 0; j < vector_size(coms); j++) {
                run_command(vector_get(coms, j), error);
            }
        } else {
            for (size_t j = 0; j <= vector_size(coms); j++) {
                rb_delete(&commands_tree, vector_get(coms, j));
            }
        }
        free(tokens);
        string_builder_destroy(file_line);
    }
    close_file(file, error);
    write_test_answer(error);
    string_builder_destroy(arg);
    printf("\nТекущий размер дерева %ld\n", global_tree_get_size());
    printf("\nВыполнения из файла завершено...\n");
}

void m_command(user_command *command, error_s *error) {
    if (command != NULL) {
        char *end = NULL;
        int64_t key = strtol(string_builder_get_string(command->arg), &end, 10);
        if (end != NULL && end[0] != 0) {
            printf("Некорректное значение аргумента для ключа.\n");
            return;
        }
        if (global_tree_is_init()) {
            printf("%ld-ый элемент: %ld \n", key, global_tree_k_stat(key));
        } else {
            printf("Дерево не инициализировано. Элементы отсутствуют.\n");
        }
    } else {
        throw_exception(error, NULL_PTR_ERROR, "m_command: передан NULL указатель.");
    }
}

void exit_command(user_command *command, error_s *error) {
    printf("%s\n", "Производится выход из программы...");
}

void print_command(user_command *command, error_s *error) {
    global_tree_print();
}

void clear_command(user_command *command, error_s *error) {
    printf("%s\n", "Очищение дерева...");
    global_tree_clear();
}

void d_command(user_command *command, error_s *error) {
    if (command != NULL) {
        printf("%s\n", "Удаление элемента...");
        char *end = NULL;
        int64_t key = strtol(string_builder_get_string(command->arg), &end, 10);
        if (end != NULL && end[0] != 0) {
            printf("Некорректное значение аргумента для ключа.\n");
            return;
        }
        global_tree_delete(key);
        rb_tree_s *founded = rb_search(commands_tree, (void *) command, command_char_arg_compare);
        rb_delete(&commands_tree, founded);
    }
}

void undefined_command(user_command *command, error_s *error) {
    printf("%s%s", "\nНекорректная команда, попробуйте ввести ещё раз!\n", "help - справка по командам\n");
}

void run_command(user_command *command, error_s *error) {
    if (command != NULL) {
        void (*command_call)(user_command *command, error_s *) = command->callback;
        command_call(command, error);
        return;
    }
    throw_exception(error, NULL_PTR_ERROR, "run_command: передан NULL указатель на command.");
}

int command_char_arg_compare(void *com1, void *com2) {
    if (com1 != NULL && com2 != NULL) {
        string_builder *com1_arg = (((user_command *) com1)->arg);
        string_builder *com2_arg = (((user_command *) com2)->arg);
        return string_builder_equals(com1_arg, com2_arg);
    }
    return -1;
}

int user_command_print(FILE *stream, char *mode, void *command) {
    return fprintf(stream, "Аргумент команды: %s", string_builder_get_string(((user_command *) command)->arg));
}
