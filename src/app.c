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
    rb_tree_print(commands_tree, user_command_to_string, 0);
}

int64_t global_tree_k_stat(size_t i) {
    if (global_tree != NULL) {
        return os_tree_get_key(os_tree_select(global_tree, i));
    }
    return 0;
}

size_t global_tree_counts_less_than(int64_t k) {
    return os_tree_find_nearest_smaller(global_tree, k);
}

void global_tree_delete(int64_t num) {
    os_tree_delete(&global_tree, num);
}

void global_tree_clear() {
    if (!os_tree_is_empty(global_tree)) {
        while (!os_tree_is_empty(global_tree)) {
            os_tree_delete(&global_tree, os_tree_get_key(global_tree));
            rb_tree_delete(&commands_tree, rb_tree_get_key(commands_tree), command_char_arg_compare,
                           user_command_destroy);
        }
    } else {
        printf("Дерево пусто!\n");
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

int ints_comparator(void* a, void* b){
    if((int64_t)a<(int64_t)b){
        return -1;
    }
    else if((int64_t)a>(int64_t)b){
        return 1;
    }
    else{
        return 0;
    }
}

//TODO переделать логику распечатки дерева;

char* int_to_string(void* a){
    return a;
}

//TODO протестить все функции
void test(){
    os_tree_s* test_os_tree;
    rb_tree_s* test_rb_tree;
    for(int i = 0; i<20; i++){
        printf("\nКруг вставки %d\n", i);
        if(i==0){
            test_rb_tree = new_rb_tree(new_object((int64_t*)i, 0));
            test_os_tree = new_os_tree(i);
        }
        else{
            rb_tree_insert(&test_rb_tree,new_object((int64_t*)i, 0), ints_comparator);
            os_tree_insert(&test_os_tree, i);
        }
        rb_tree_print(test_rb_tree, int_to_string, 0);
        os_tree_print(test_os_tree, 0);
    }
    for(int i = 0; i<20; i++){
        printf("\nКруг удаления %d\n", i);
        if(i == 4){
            rb_tree_delete(&test_rb_tree, new_object((int64_t*)i, 0), ints_comparator, free);
            os_tree_delete(&test_os_tree, i);
            rb_tree_print(test_rb_tree, int_to_string, 0);
            os_tree_print(test_os_tree, 0);
            continue;
        }
        rb_tree_delete(&test_rb_tree, new_object((int64_t*)i, 0), ints_comparator, free);
        os_tree_delete(&test_os_tree, i);
        rb_tree_print(test_rb_tree, int_to_string, 0);
        os_tree_print(test_os_tree, 0);
    }
}

int app_start(error_s *error) {
    print_greeting();
    test();
    return 0;
    console(error);
    global_tree_destroy();
    global_tree = NULL;
    return 0;
}