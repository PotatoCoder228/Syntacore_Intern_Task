cmake_minimum_required(VERSION 3.16)
project(Syntacore_Tools_Intern_Task C)

set(CMAKE_C_STANDARD 11)

add_executable(Syntacore_Tools_Intern_Task src/main_app/main.c src/io/io_stream_handler.c include/io_stream_handler.h src/main_app/app.c include/app.h src/status/app_status.c include/app_status.h)
