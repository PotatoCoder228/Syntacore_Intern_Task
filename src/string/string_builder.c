//
// Created by sasha on 04.03.2023.
//

#include "../../include/string/string_builder.h"
#include "../../include/containers/containers.h"

typedef struct string_builder {
    char *string;
    size_t size;
} string_builder;

string_builder *new_string_builder() {
    string_builder *builder = malloc(sizeof(string_builder));
    if (builder != NULL) {
        builder->string = malloc(sizeof(char));
        (builder->string)[0] = '\0';
        builder->size = strlen(builder->string);
    } else {
        printf("%s", strerror(errno));
    }
    return builder;
}

void string_builder_set_string(string_builder *string_builder, const char *new_string) {
    if (string_builder != NULL) {
        size_t size = strlen(new_string);
        if (string_builder->string == NULL) {
            string_builder->string = malloc(sizeof(char) * (size + 1));
            if (string_builder->string != NULL) {
                string_builder->size = size;
            }
            string_builder->string[size] = '0';
        } else {
            string_builder->string = realloc(string_builder->string, sizeof(char) * (size + 1));
            if (string_builder->string != NULL) {
                string_builder->size = size;
            }
            string_builder->string[size] = '0';
        }
        strcpy(string_builder->string, new_string);
    }
}

char *string_builder_get_string(string_builder *builder) {
    if (builder == NULL) {
        return NULL;
    }
    return builder->string;
}

char *string_builder_to_string(void *builder) {
    if (builder == NULL) {
        return NULL;
    }
    return ((string_builder *) builder)->string;
}

bool string_builder_concat(string_builder *main, string_builder *from) {
    if (main != NULL && from != NULL) {
        main->string = realloc(main->string, (main->size) + (from->size) + 1);
        if (main->string != NULL) {
            strcat(main->string, from->string);
            main->size = strlen(main->string);
            return true;
        }
        return false;
    }
    return false;
}

vector_s *string_builder_get_tokens(string_builder *string, char *sep) {
    vector_s *result = new_vector();
    if (result == NULL || string == NULL) {
        return NULL;
    }
    char *buf;
    string_builder *token;

    buf = strtok(string->string, sep);
    while (buf != NULL) {
        token = new_string_builder();
        if (token == NULL) {
            vector_destroy(result, string_builder_destroy);
            return NULL;
        }
        string_builder_set_string(token, buf);
        vector_push(result, new_object(token, IN_HEAP));
        buf = strtok(NULL, sep);
    }
    return result;
}

void string_builder_destroy(void *builder) {
    if (builder != NULL) {
        char *str = string_builder_get_string((string_builder *) builder);
        if (str != NULL) {
            free(str);
        }
        free((string_builder *) builder);
    }
}

int string_builder_equals(string_builder *builder_1, string_builder *builder_2) {

    if (strcmp(builder_1->string, builder_2->string) == 0) {
        return 0;
    } else if (strcmp(builder_1->string, builder_2->string) > 0) {
        return -1;
    }
    return 1;
}