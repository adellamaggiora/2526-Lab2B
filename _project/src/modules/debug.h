#ifndef DEBUG_H
#define DEBUG_H

#include "graph.h"

void debug_print_hash_table(arco **hash_table, int table_length);

void debug_print_edge(arco *edge);

void debug_print_pointer(void *pointer, void (*printer_function)(void *elem));

void debug_print_pointer_list(void **list, size_t list_length, void (*printer_function)(void *elem));

void debug_print_array(void *list, size_t list_length, size_t elem_size, void (*printer_function)(void *elem));

#endif
