#include <stdio.h>
#include "debug.h"

void debug_print_hash_table(arco **hash_table, int table_length)
{
    for (int i = 0; i < table_length; i++)
    {
        arco *edge = hash_table[i];
        printf("gHash[%d]:", i);
        printf("\n");
        while (edge != NULL)
        {
            debug_print_edge(edge);
            edge = edge->next;
        }
    }
}

void debug_print_edge(arco *edge)
{
    printf("->(u %d, v %d, w %d, msf %s)",
           edge->u, edge->v, edge->weight,
           edge->msf ? "true" : "false");
    printf("\n");
}

// prende una funzione come parametro
void debug_print_pointer(void *pointer, void (*printer_function)(void *elem))
{
    if (printer_function != NULL)
    {
        printer_function(pointer);
    }
}

void debug_print_pointer_list(
    void **list,
    size_t list_length,
    void (*printer_function)(void *elem))
{
    for (size_t i = 0; i < list_length; i++)
    {
        void *pointer = list[i];
        debug_print_pointer(pointer, printer_function);
    }
}

void debug_print_array(
    void *list,
    size_t list_length,
    size_t elem_size,
    void (*printer_function)(void *elem))
{
    // char = 1 byte -> posso spostare facilmente il puntatore di elem_size byte
    char *ptr = list;

    for (size_t i = 0; i < list_length; i++)
    {
        printer_function(ptr);
        ptr += elem_size;
    }
}
