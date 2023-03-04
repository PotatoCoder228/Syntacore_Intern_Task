//
// Created by sasha on 04.03.2023.
//

#include "../../include/io/io_handler.h"


void open_file(FILE **stream, char *filename, enum open_file_modes mode, error_s *error) {
    *stream = fopen(filename, open_file_modes[mode]);
    if (*stream == NULL) {
        throw_exception(error, errno, strerror(errno));
    } else {
        error_set_default(error);
    }
}

void close_file(FILE **stream, error_s *error) {
    int status = fclose(*stream);
    if (status) {
        throw_exception(error, errno, strerror(errno));
    } else {
        error_set_default(error);
    }
}