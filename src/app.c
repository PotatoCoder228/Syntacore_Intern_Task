//
// Created by sasha on 04.03.2023.
//

#include "../include/app.h"
#include "../include/console/console.h"

os_tree_s *global_tree = NULL;

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

int64_t global_tree_k_stat(size_t i) {
    if (global_tree != NULL) {
        return os_tree_get_key(os_tree_select(global_tree, i));
    }
    return 0;
}

size_t global_tree_counts_less_than(int64_t k) {
    return os_tree_find_counts_less_than(global_tree, k);
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
    os_tree_print(global_tree, 0);
    global_tree_destroy(global_tree);
    global_tree = NULL;
    return 0;
}