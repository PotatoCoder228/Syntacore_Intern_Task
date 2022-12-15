//
// Created by potato_coder on 13.12.22.
//

#include "tests.h"
#include "time.h"
#include "../../include/singly_linked_list.h"

#include <string.h>

char *get_format_time_now() {
    time_t now = time(0);
    char *time = ctime(&now);
    char *result_time = malloc(sizeof(char) * 26);
    result_time[0] = '[';
    result_time[25] = ']';
    for (int i = 1; i <= 24; i++) {
        result_time[i] = time[i - 1];
    }
    return result_time;
}

void print_log(FILE *stream, char *info) {
    char *time = get_format_time_now();
    fprintf(stream, "%s", "\n");
    fprintf(stream, "%s", time);
    fprintf(stream, "%s", "[");
    fprintf(stream, "%s", info);
    fprintf(stream, "%s", "]\n");
}

int linked_list_test() {
    fflush_unlocked(stdout);
    print_log(stderr, "##########Test start!##########");
    print_log(stderr, "linked_list_init() testing...");
    linked_list *list = linked_list_init("List init string");
    if (list == NULL) {
        print_log(stderr, "linked_list_init() is failed test.");
        print_log(stderr, "##########Test finish!##########");
        return -1;
    }
    print_log(stderr, "linked_list_init() is successful.");
    fflush(stdout);
    print_log(stderr, "linked_list_push() testing...");
    linked_list_push(list, "First test string");
    linked_list_push(list, "Second test string");
    linked_list_push(list, "Third test string");
    print_log(stderr, "Push 3 values. 4 values in list.");

    if (strcmp(list->value, "List init string") != 0) {
        print_log(stderr, "linked_list_push() is failed test.");
        print_log(stderr, "##########Test finish!##########");
        return -1;
    }
    print_log(stderr, "linked_list_push() is successful.");
    fflush(stdout);
    print_log(stderr, "linked_list_pop testing...");
    void *value = linked_list_pop(list);
    if (value == NULL || strcmp(value, "Third test string") != 0) {
        print_log(stderr, "linked_list_pop() is failed test.");
        print_log(stderr, "##########Test finish!##########");
        return -1;
    }
    print_log(stderr, "Current list values:");
    print_linked_list(stderr, "%s", list);
    print_log(stderr, "linked_list_pop() is successful.");
    fflush(stdout);
    print_log(stderr, "linked_list_get_last() testing...");
    value = linked_list_get_last(list);
    if (value == NULL || strcmp(value, "Second test string") != 0) {
        print_log(stderr, "linked_list_get_last() is failed test.");
        print_log(stderr, "##########Test finish!##########");
        return -1;
    }
    print_log(stderr, "linked_list_get_last() is successful.");
    fflush(stdout);
    print_log(stderr, "linked_list_add_first() testing...");
    int num = 1;
    linked_list_add_first(&list, &num);
    if (*((int *) (list->value)) != 1) {
        print_log(stderr, "linked_list_add_first() is failed test.");
        print_log(stderr, "##########Test finish!##########");
        return -1;
    }
    print_log(stderr, "linked_list_add_first() is successful.");
    fflush(stdout);
    print_log(stderr, "linked_list_add_last() testing...");
    linked_list_add_last(list, "Insert last");
    if (strcmp(linked_list_get_last(list), "Insert last") != 0) {
        print_log(stderr, "linked_list_add_last() is failed test.");
        print_log(stderr, "##########Test finish!##########");
        return -1;
    }
    print_log(stderr, "linked_list_add_last() is successful.");
    fflush(stdout);
    print_log(stderr, "linked_list destroy...");
    list_destroy(list);
    print_log(stderr, "##########Test finish!##########");
    return 0;
}