//
// Created by sasha on 04.03.2023.
//

#include "../../include/exceptions/error_s.h"

typedef struct error_s {
    string_builder *message;
    int code;
} error_s;

error_s *new_error() {
    error_s *error = malloc(sizeof(error_s));
    error->message = NULL;
    error->code = 0;
    return error;
}

void error_set_message(error_s *error, string_builder *message) {
    error->message = message;
}

string_builder *error_get_message(error_s *error) {
    if (error == NULL) {
        return NULL;
    }
    return error->message;
}

void error_set_code(error_s *error, int code) {
    if (error != NULL) {
        error->code = code;
    }
}

int error_get_code(error_s *error) {
    if (error != NULL) {
        return error->code;
    }
    return INT_MAX;
}

void error_print(error_s *error) {
    printf("%s\n", string_builder_to_string(error_get_message(error)));
}

char *error_to_string(void *error) {
    if (error == NULL) {
        return NULL;
    }
    return string_builder_to_string(((error_s *) error)->message);
}

void error_print_to(FILE *stream, error_s *error) {
    fprintf(stream, "%s\n", string_builder_to_string(error_get_message(error)));
}

void throw_exception(error_s *error, int code, char *message) {
    if (error != NULL) {
        string_builder *string = new_string_builder();
        string_builder_set_string(string, message);
        error_set_code(error, code);
        error_set_message(error, string);
        fprintf(stderr, "\n");
        error_print_to(stderr, error);
        exit(EXIT_FAILURE);
    }
}

void error_set_default(error_s *error) {
    error_set_code(error, 0);
    string_builder *builder = new_string_builder();
    string_builder_set_string(builder, "All are OK");
    error_set_message(error, builder);
}

void error_destroy(void *error) {
    string_builder_destroy((void *) error_get_message((error_s *) error));
    free((error_s *) error);
}