CC = gcc

CFLAGS = -g -Wall -Wextra -std=gnu11 -pthread
INCLUDES = -Ilib/tomlc17 -Isrc/modules

# Linka la libreria matematica libm
LDLIBS = -lm

TARGET = build/main

HEADERS = $(wildcard src/modules/*.h)

SOURCES = src/main.c \
	src/modules/graph.c \
	src/modules/hash.c \
	src/modules/msf.c \
	src/modules/parser.c \

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET) $(LDLIBS)

clean:
	rm -rf build