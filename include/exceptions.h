//
// Created by potato_coder on 04.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_EXCEPTIONS_H
#define SYNTACORE_TOOLS_INTERN_TASK_EXCEPTIONS_H

enum file_exceptions {
    FILE_OPEN_ERROR = 1,
    FILE_CLOSE_ERROR = 2,
    FILE_READ_ERROR = 3,
};

enum command_exceptions {
    UNCORRECT_COMMAND = 4,
    UNCORRECT_ARGUMENT = 5,
    KEY_IS_EXISTS = 6
};


#endif //SYNTACORE_TOOLS_INTERN_TASK_EXCEPTIONS_H
