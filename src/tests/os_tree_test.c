//
// Created by sasha on 08.03.2023.
//

#include <bits/types/time_t.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/containers/containers.h"

static char *get_format_time_now() {
    time_t now = time(0);
    char *time = ctime(&now);
    char *result_time = malloc(sizeof(char) * 27);
    result_time[0] = '[';
    result_time[25] = ']';
    result_time[26] = '\0';
    for (int i = 1; i <= 24; i++) {
        result_time[i] = time[i - 1];
    }
    return result_time;
}

void print_log(FILE *stream, char *info) {
    char *time = get_format_time_now();
    fprintf(stream, "%s%s%s%s%s", "\n", time, "[", info, "]\n");
}


static void os_tree_test() {
    print_log(stdout, "Старт теста на вставку и удаление из OS-дерева.");
    print_log(stdout, "P.S. для диагностики утечек памяти - запустите тест с помощью valgrind");
    print_log(stdout, "Инициализируем дерево...");
    os_tree_s *tree = new_os_tree(100);
    os_delete(&tree, tree);
    if (tree == NULL) {
        print_log(stderr, "Не удалось выделить память под дерево.");
        print_log(stderr, "Тест провален.");
        exit(0);
    }
    print_log(stdout, "Дерево успешно инициализировано.");
    os_tree_s *found_node;
    print_log(stdout, "Вставляем 1000000 элементов от 0 до 999999");
    for (int i = 0; i < 1000000; i++) {
        os_insert(&tree, new_os_tree_node(i));
    }
    print_log(stdout, "Проверяем поля size...");
    for (int64_t i = 0; i < 1000000; i++) {
        found_node = os_search(tree, i);
        if (os_size(found_node) !=
            (os_size(os_right(found_node)) + os_size(os_left(found_node)) + 1)) {
            print_log(stderr, "Проверка size провалилась...");
            exit(0);
        }
    }
    print_log(stdout, "Поля size заданы корректно...");
    os_tree_s *iter = os_start(tree);
    print_log(stdout, "Тестируем итерацию...");
    for (int64_t i = 0; os_has_next(iter) != false; i++) {
        if (os_key(iter) != i) {
            print_log(stderr, "Тест итератора провалился.");
            printf("%ld, i: %ld\n", os_key(iter), i);
            exit(0);
        }
        iter = os_next(iter);
    }
    print_log(stdout, "Тест итератора прошёл успешно.");
    print_log(stdout, "Последовательно ищем элементы от 0 до 999999 и удаляем...");
    for (int i = 0; i < 1000000; i++) {
        found_node = os_search(tree, i);
        if (os_node_is_empty(found_node)) {
            print_log(stderr, "Вставка и поиск по дереву завершились неудачей.");
            exit(0);
        }
        os_delete(&tree, found_node);
    }
    os_destroy(tree);
    print_log(stdout, "Тест успешно пройден.");
}

int main() {
    os_tree_test();
    return 0;
}