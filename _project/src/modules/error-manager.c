#include "error-manager.h"

#include <errno.h>
#include <stdlib.h>

void terminate(const char *message)
{
    if (errno != 0)
        perror(message);
    else
        fprintf(stderr, "%s\n", message);

    exit(EXIT_FAILURE);
}

FILE *checked_fopen(const char *path, const char *mode)
{
    FILE *file = fopen(path, mode);
    if (file == NULL)
        terminate("File opening failed");

    return file;
}

void *checked_malloc(size_t size)
{
    void *pointer = malloc(size);
    if (pointer == NULL)
        terminate("Memory allocation failed");

    return pointer;
}

void *checked_calloc(size_t count, size_t size)
{
    void *pointer = calloc(count, size);
    if (pointer == NULL)
        terminate("Memory allocation failed");

    return pointer;
}

void *checked_realloc(void *pointer, size_t size)
{
    void *new_pointer = realloc(pointer, size);
    if (new_pointer == NULL)
        terminate("Memory reallocation failed");

    return new_pointer;
}
