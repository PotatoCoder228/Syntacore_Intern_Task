cmake_minimum_required(VERSION 3.16)
project(Syntacore_Tools_Intern_Task C)

set(CMAKE_C_STANDARD 11)

add_executable(Syntacore_Tools_Intern_Task src/main_app/main.c src/io/io_stream_handler.c include/io_stream_handler.h src/main_app/app.c include/app.h src/exceptions/exceptions.c include/exceptions.h src/containers/singly_linked_list.c include/singly_linked_list.h src/commands/commands.c include/commands.h src/tests/tests.c src/tests/tests.h)
