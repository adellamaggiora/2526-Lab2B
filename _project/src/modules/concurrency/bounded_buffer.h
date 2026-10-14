#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H


#include <pthread.h>
#include <graph_operation.h>


// quali sono le prop del buffer? head e tail servono


typedef struct bounded_buffer {
    // numero massimo elementi nella coda
    int capacity;

    // indice estrazione op
    int head;

    // indice inserimento op
    int tail;

    graph_operation *queue;

    // mutex per mutua esclusione per acesso e modifica indici
    pthread_mutex_t mutex;
    // cv per garantire condizioni valide di inserimento 
    pthread_cond_t is_full;
    pthread_cond_t is_empty;


} bounded_buffer;



#endif