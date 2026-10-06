#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <stddef.h>
#include <stdio.h>

void terminate(const char *message);

FILE *checked_fopen(const char *path, const char *mode);
void *checked_malloc(size_t size);
void *checked_calloc(size_t count, size_t size);
void *checked_realloc(void *pointer, size_t size);

#endif
