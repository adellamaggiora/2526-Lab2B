CC := gcc

CPPFLAGS := -Isrc/modules -Isrc/modules/graph
CFLAGS := -O3 -Wall -Wextra -std=gnu11 -pthread
LDFLAGS := -pthread
LDLIBS := -lm

TARGET := msf.out

SOURCES := \
	src/main.c \
	src/modules/concurrency/bounded_buffer.c \
	src/modules/concurrency/graph_operation.c \
	src/modules/graph/graph.c \
	src/modules/graph/hash.c \
	src/modules/graph/msf.c \
	src/modules/graph/union_find.c \
	src/modules/io/graph_parser.c \
	src/modules/io/operation_parser.c \
	src/modules/io/parser_utils.c \
	src/modules/utils/debug.c \
	src/modules/utils/error-manager.c
OBJECTS := $(patsubst src/%.c,build/%.o,$(SOURCES))
DEPENDENCIES := $(OBJECTS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPENDENCIES)

clean:
	rm -rf build $(TARGET)
