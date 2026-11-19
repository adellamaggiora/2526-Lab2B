CC := gcc
CFLAGS := -g -O0 -Wall -Wextra -Werror=vla -std=gnu11 -pthread
CPPFLAGS := -Isrc/modules -Isrc/modules/concurrency -Isrc/modules/graph -Isrc/modules/utils
SOURCES := $(wildcard src/*.c src/modules/*/*.c)
ARGS ?= -t 3 msf/minimo.gr msf/minimo.mp

.PHONY: all debug memory-check clean

all: msf.out

msf.out: $(SOURCES) $(wildcard src/modules/*/*.h)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@ -lm

debug:
	$(MAKE) -B msf.out
	gdbgui --remote --port 5000 --args ./msf.out $(ARGS)

memory-check:
	$(MAKE) -B msf.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./msf.out $(ARGS)

clean:
	rm -f msf.out
