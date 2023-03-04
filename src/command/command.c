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

void *user_command_get_callback(user_command *command) {
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
            printf("Количество чисел, меньших, чем %ld: %ld\n", key, global_tree_counts_less_than(key));
        } else {
            printf("Дерево не инициализировано. Элементы отсутствуют.\n");
        }
    }
}

void script_command(user_command *command, error_s *error) {
    printf("Введите имя файла:");
    string_builder *arg = read_line(stdin, error);
    if (arg == NULL) {
        throw_exception(error, INPUT_STREAM_READ_ERROR, "script command: Не удалось прочитать строку.");
    }
    FILE *file = NULL;
    open_file(&file, string_builder_get_string(arg), R, error);
    if (file == NULL) {
        string_builder_destroy(arg);
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
        for (size_t i = 0; i < vector_get_size(tokens); i += 2) {
            user_command *com = parse_and_set_tree_command(tokens, i);
            if (com == NULL) {
                printf("Некорректная команда.");
                rb_tree_destroy(commands_tree, user_command_destroy);
                commands_tree = NULL;
                break;
            }
            if (user_command_get_callback(com) == k_command) {
                object_s *key = new_object(com, IN_HEAP);
                //rb_tree_print(commands_tree, user_command_to_string,0);
                rb_tree_s *buf = rb_tree_search(commands_tree, key, command_char_arg_compare);
                if (rb_tree_get_key(buf) == NULL) {
                    if (commands_tree == NULL) {
                        commands_tree = new_rb_tree(key);
                    } else {
                        rb_tree_insert(&commands_tree, key, command_char_arg_compare);
                    }
                    vector_push(coms, key);
                } else {
                    printf("В последовательности команд было несколько k c одинаковыми аргументами.\n");
                    printf("Либо какое-то из чисел уже есть в дереве.\n");
                    break;
                }
            } else {
                object_s *key = new_object(com, IN_HEAP);
                vector_push(coms, key);
            }
        }
        if (commands_tree != NULL) {
            for (size_t j = 0; j < vector_get_size(coms); j++) {
                run_command(object_get_value(vector_get(coms, j)), error);
            }
        } else {
            for (size_t j = 0; j < vector_get_size(coms); j++) {
                rb_tree_delete(&commands_tree, object_get_value(vector_get(coms, j)), command_char_arg_compare,
                               user_command_destroy);
            }
        }
        //rb_tree_print(commands_tree, user_command_to_string,0);
        free(tokens);
        string_builder_destroy(file_line);
    }
    close_file(&file, error);
    string_builder_destroy(arg);
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
            printf("%ld-ый наименьший элемент: %ld\n", key, global_tree_k_stat(key));
        } else {
            printf("Дерево не инициализировано. Элементы отсутствуют.\n");
        }
    }
}

void exit_command(user_command *command, error_s *error) {
    printf("%s\n", "Производится выход из программы...");
}

void print_command(user_command *command, error_s *error) {
    global_tree_print();
}

void clear_command(user_command *command, error_s *error) {
    global_tree_clear();
    printf("%s\n", "Очищение дерева...");
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
        rb_tree_delete(&commands_tree, new_object(command, IN_HEAP), command_char_arg_compare, user_command_destroy);
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
        return string_builder_equals((((user_command *) com1)->arg), (((user_command *) com2)->arg));
    }
    return 0;
}

char *user_command_to_string(void *command) {
    return string_builder_to_string((((user_command *) command)->arg));
}