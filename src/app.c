//
// Created by sasha on 04.03.2023.
//

#include "../include/app.h"
#include "../include/console/console.h"
#include "../include/containers/containers.h"

os_tree_s *global_tree = NULL;
extern rb_tree_s *commands_tree;

bool global_tree_is_init() {
    if (global_tree != NULL) {
        return true;
    }
    return false;
}

bool global_tree_init(int64_t key) {
    global_tree = new_os_tree(key);
    if (global_tree) {
        return true;
    }
    return false;
}

bool global_tree_insert(int64_t key) {
    if (global_tree != NULL) {
        os_tree_insert(&global_tree, key);
        return true;
    }
    return false;
}

void global_tree_print() {
    os_tree_print(global_tree, 0);
}

int64_t global_tree_k_stat(size_t i) {
    if (global_tree != NULL) {
        return os_tree_get_key(os_tree_select(global_tree, i));
    }
    return 0;
}

size_t global_tree_counts_less_than(int64_t k) {
    return os_tree_find_counts_less_than(global_tree, k);
}

void global_tree_delete(int64_t num) {
    os_tree_delete(&global_tree, num);
}

void global_tree_clear() {
    if (global_tree != NULL) {
        while (os_tree_get_size(global_tree) > 1) {
            os_tree_delete(&global_tree, os_tree_get_key(global_tree));
            rb_tree_delete(&commands_tree, rb_tree_get_key(commands_tree), command_char_arg_compare,
                           user_command_destroy);
        }
        os_tree_delete(&global_tree, os_tree_get_key(global_tree));
        rb_tree_delete(&commands_tree, rb_tree_get_key(commands_tree), command_char_arg_compare, user_command_destroy);
        os_tree_print(global_tree, 0);
        rb_tree_print(commands_tree, user_command_to_string, 0);
    }
}

void global_tree_destroy() {
    if (global_tree != NULL) {
        os_tree_destroy(global_tree);
    }
}

static void print_greeting() {
    printf("%s\n", "████──████──███──████──███──████──████──████──████───███──████──████──████──████\n"
                   "█──█──█──█───█───█──█───█───█──█──█──█──█──█──█──██──█────█──█──█──█──█──█──█──█\n"
                   "████──█──█───█───████───█───█──█──█─────█──█──█──██──███──████────██────██──████\n"
                   "█─────█──█───█───█──█───█───█──█──█──█──█──█──█──██──█────█─█───██────██────█──█\n"
                   "█─────████───█───█──█───█───████──████──████──████───███──█─█───████──████──████");

    printf("%s\n", "\nДобро пожаловать в консольное приложение.");
}

int app_start(error_s *error) {
    print_greeting();
    console(error);
    global_tree_destroy();
    global_tree = NULL;
    return 0;
}