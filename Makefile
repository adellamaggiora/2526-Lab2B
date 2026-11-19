CC := gcc

DOCKER ?= docker
IMAGE ?= lab2
DEBUG_PORT ?= 5000
FILE ?= msf/minimo.gr
export FILE

DOCKER_RUN = $(DOCKER) run --rm -v "$(CURDIR):/workspace" -w /workspace

CPPFLAGS := -Isrc/modules -Isrc/modules/concurrency -Isrc/modules/graph -Isrc/modules/utils
CFLAGS := -O0 -g -Wall -Wextra -Werror=vla -std=gnu11 -pthread
LDFLAGS := -pthread
LDLIBS := -lm

TARGET := build/msf.out

SOURCES := \
	src/main.c \
	src/modules/concurrency/bounded_buffer.c \
	src/modules/concurrency/consumer.c \
	src/modules/graph/graph_operation.c \
	src/modules/data_structures/circular_buffer.c \
	src/modules/graph/components.c \
	src/modules/graph/graph.c \
	src/modules/graph/hash.c \
	src/modules/graph/msf.c \
	src/modules/graph/union_find.c \
	src/modules/io/graph_parser.c \
	src/modules/io/operation_parser.c \
	src/modules/io/parser_utils.c \
	src/modules/utils/debug.c \
	src/modules/utils/xerrori.c
OBJECTS := $(patsubst src/%.c,build/%.o,$(SOURCES))
DEPENDENCIES := $(OBJECTS:.o=.d)

.PHONY: all clean help image dev run valgrind ensure-image check-file

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPENDENCIES)

clean:
	rm -rf build msf.out

help:
	@printf '%s\n' \
		'make / make all                   	Compila build/msf.out (ambiente corrente)' \
		'make clean                        	Rimuove i file di compilazione' \
		"make image                        	Costruisce o aggiorna l'immagine Docker" \
		'make dev [FILE=percorso.gr]        Compila, avvia gdbgui su localhost:5000 e apre Bash' \
		'make run [FILE=percorso.gr]        Compila ed esegue nel container' \
		'make valgrind [FILE=percorso.gr]   Compila e controlla la memoria nel container' \
		'make help                         	Mostra questa lista' \
		'Variabili: IMAGE=lab2, DEBUG_PORT=5000, FILE=msf/minimo.gr'

image:
	$(DOCKER) build -t "$(IMAGE)" .

ensure-image:
	@$(DOCKER) image inspect "$(IMAGE)" >/dev/null 2>&1 || $(MAKE) --no-print-directory image

check-file:
	@test -f "$$FILE" || { printf 'File di input non trovato: %s\n' "$$FILE" >&2; exit 1; }

dev: check-file ensure-image
	$(DOCKER_RUN) --init -it -p "127.0.0.1:$(DEBUG_PORT):5000" \
		--env FILE --env DEBUG_PORT="$(DEBUG_PORT)" "$(IMAGE)" bash scripts/dev.sh "$(TARGET)"

run: check-file ensure-image
	$(DOCKER_RUN) --env FILE "$(IMAGE)" sh -c 'make && exec ./$(TARGET) "$$FILE"'

valgrind: check-file ensure-image
	$(DOCKER_RUN) --env FILE "$(IMAGE)" sh -c \
		'make && exec valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./$(TARGET) "$$FILE"'
