cmake_minimum_required(VERSION 3.16)
project(Syntacore_Tools_Intern_Task)

set(CMAKE_C_STANDARD 11)

add_executable(Syntacore_Tools_Intern_Task src/command/command.c include/command/command.h src/console/console.c include/console/console.h src/containers/os_tree_s.c include/containers/os_tree_s.h src/containers/rb_tree_s.c include/containers/rb_tree_s.h src/object/object.c include/object/object.h src/containers/list_s.c include/containers/list_s.h include/containers/containers.h src/app.c include/app.h src/main.c src/containers/vector_s.c include/containers/vector_s.h include/containers/cont-common.h src/exceptions/error_s.c include/exceptions/error_s.h src/string/string_builder.c include/string/string_builder.h)
