#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stddef.h>



typedef struct circular_buffer
{
    // da dove iniziano i dati in memoria
    void *data;

    int element_size;
    int capacity;
    int size;

    // dove si estrae
    int head;

    // dove si inserisce
    int tail;
} circular_buffer;



void circular_buffer_init(circular_buffer *buffer, int capacity, int element_size);
void circular_buffer_destroy(circular_buffer *buffer);


bool circular_buffer_is_empty(const circular_buffer *buffer);
bool circular_buffer_is_full(const circular_buffer *buffer);


bool circular_buffer_push(circular_buffer *buffer, const void *element);
bool circular_buffer_pop(circular_buffer *buffer, void *element);



#endif
