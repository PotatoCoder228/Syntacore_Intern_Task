#include <stdio.h>
#include "../../include/app.h"
#include "../../include/singly_linked_list.h"

int main(void) {
    //return app_start();
    linked_list* list = linked_list_init("Hello there");
    linked_list_push(list, "Первая строка\0");
    linked_list_push(list, "Вторая строка строка\0");
    linked_list_push(list, "Третья строка\0");
    void* value = linked_list_pop(list);
    printf("%s\n", value);
    printf("%s\n", linked_list_get_last(list));
    linked_list_add_first(&list, "Вставил в начало списка");
    linked_list_add_last(list, "Вставил в конец списка");
    printf("%s\n", linked_list_get_last(list));
    printf("%s\n", list -> value);
    printf("%s\n", linked_list_get(list, 10));

    linked_list* clone;
    linked_list_clone(list, &clone);
    printf("%s", clone->value);
    return 0;
}
