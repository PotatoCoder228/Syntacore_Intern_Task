//
// Created by sasha on 04.03.2023.
//

#include "../../include/io/io_handler.h"


FILE *open_file(char *filename, enum open_file_modes mode, error_s *error) {
    FILE *stream = fopen(filename, open_file_modes[mode]);
    if (stream == NULL) {
        error_set_code(error, errno);
        string_builder *err_msg = new_string_builder();
        string_builder_set_string(err_msg, strerror(errno));
        error_set_message(error, err_msg);
        error_print(error);
        return NULL;
    } else {
        error_set_default(error);
        return stream;
    }
}

void close_file(FILE *stream, error_s *error) {
    int status = fclose(stream);
    if (status) {
        throw_exception(error, errno, strerror(errno));
    } else {
        error_set_default(error);
    }
}