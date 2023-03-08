CC = gcc
CFLAGS = -c -Wall -O2
SOURCES = src/command/command.c include/command/command.h src/console/console.c include/console/console.h src/containers/os_tree_s.c include/containers/os_tree_s.h src/containers/rb_tree_s.c include/containers/rb_tree_s.h src/containers/list_s.c include/containers/list_s.h include/containers/containers.h src/app.c include/app.h src/main.c src/containers/vector_s.c include/containers/vector_s.h include/containers/cont-common.h src/exceptions/error_s.c include/exceptions/error_s.h src/string/string_builder.c include/string/string_builder.h src/io/io_handler.c include/io/io_handler.h
EXECUTABLE = SyntacoreInternTask
OBJECTS=$(SOURCES:.cpp=.o)
LDFLAGS=

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
