#include "data_structures/circular_buffer.h"
#include "utils/error-manager.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void circular_buffer_init(circular_buffer *buffer, int capacity, int element_size)
{
    assert(buffer != NULL);
    assert(capacity > 0);
    assert(element_size > 0);

    buffer->data = checked_calloc(capacity, element_size);
    buffer->element_size = element_size;
    buffer->capacity = capacity;
    buffer->size = 0;
    buffer->head = 0;
    buffer->tail = 0;
}

void circular_buffer_destroy(circular_buffer *buffer)
{
    assert(buffer != NULL);

    free(buffer->data);
    buffer->data = NULL;
    buffer->element_size = 0;
    buffer->capacity = 0;
    buffer->size = 0;
    buffer->head = 0;
    buffer->tail = 0;
}

bool circular_buffer_is_empty(const circular_buffer *buffer)
{
    assert(buffer != NULL);
    return buffer->size == 0;
}

bool circular_buffer_is_full(const circular_buffer *buffer)
{
    assert(buffer != NULL);
    return buffer->size == buffer->capacity;
}

bool circular_buffer_push(circular_buffer *buffer, const void *element)
{
    assert(buffer != NULL);
    assert(element != NULL);

    if (circular_buffer_is_full(buffer))
    {

        return false;
    }
    

    // il problema di questa riga è che data, essendo un puntatore a void,
    // non sa di quanti byte deve spostarsi, quindi devo trattare data come char (1 byte)
    // char *insert_address = buffer->data + (buffer->element_size * buffer->tail);

    char *start_address = buffer->data;
    char *insert_address = start_address + (buffer->element_size * buffer->tail);
    memcpy(insert_address, element, buffer->element_size);

    // circolarità
    buffer->tail++;
    buffer->tail = buffer->tail % buffer->capacity;
    buffer->size++;

    return true;

}

bool circular_buffer_pop(circular_buffer *buffer, void *element)
{
    assert(buffer != NULL);
    assert(element != NULL);

    if (circular_buffer_is_empty(buffer))
    {
        return false;
    }


}
