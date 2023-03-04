//
// Created by sasha on 04.03.2023.
//

#include "../../include/object/object.h"


typedef struct object_s {
    void *value;
    enum object_is in_heap;
} object_s;

object_s *new_object(void *value, enum object_is in_heap) {
    object_s *new_object = malloc(sizeof(object_s));
    new_object->value = value;
    new_object->in_heap = in_heap;
    return new_object;
}

void *object_get_value(object_s *object) {
    if (object != NULL) {
        return object->value;
    }
    return NULL;
}

char *object_to_string(object_s *object, char *to_string(void *)) {
    if (object != NULL) {
        return to_string(object->value);
    }
    return NULL;
}

enum object_is object_get_in_heap(object_s *object) {
    return object->in_heap;
}

void object_destroy(object_s *object, void (*destroyer)(void *)) {
    if (object != NULL) {
        if (object->in_heap == IN_HEAP && object->value != NULL) {
            destroyer(object->value);
        }
        free(object);
    }
}

int object_compare(void *first, void *second, int(*compare)(void *, void *)) {
    return compare(((object_s *) first)->value, ((object_s *) second)->value);
}
