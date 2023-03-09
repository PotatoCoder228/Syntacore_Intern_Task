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
        os_insert(&global_tree, new_os_tree_node(key));
        return true;
    }
    return false;
}


void global_tree_print() {
    os_print(global_tree, 0);
    printf("Элементы в порядке возрастания:\n");
    os_inorder_print(stdout, global_tree);
}

int64_t global_tree_k_stat(size_t i) {
    if (global_tree != NULL) {
        return os_key(os_select(global_tree, i));
    }
    return 0;
}

size_t global_tree_counts_less_than(int64_t k) {
    return os_find_less_than(global_tree, k);
}

void global_tree_delete(int64_t num) {
    os_tree_s *founded = os_search(global_tree, num);
    if (os_node_is_empty(founded)) {
        printf("Элемент отсутствует в дереве.\n");
    } else {
        os_delete(&global_tree, founded);
    }
}

void global_tree_clear() {
    if (!os_node_is_empty(global_tree)) {
        while (!os_node_is_empty(global_tree)) {
            os_delete(&global_tree, global_tree);
            rb_delete(&commands_tree, commands_tree);
        }
    } else {
        printf("Дерево пусто!\n");
    }
}

void global_tree_destroy() {
    if (global_tree != NULL) {
        os_destroy(global_tree);
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
    return 0;
}