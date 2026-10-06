#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <stddef.h>
#include <stdio.h>
#include <pthread.h>

void terminate(const char *message);

FILE *checked_fopen(const char *path, const char *mode);
void *checked_malloc(size_t size);
void *checked_calloc(size_t count, size_t size);
void *checked_realloc(void *pointer, size_t size);

int checked_pthread_create(
    pthread_t *thread,
    const pthread_attr_t *attributes,
    void *(*start_routine)(void *),
    void *argument);
int checked_pthread_join(pthread_t thread, void **return_value);

int checked_pthread_mutex_init(
    pthread_mutex_t *mutex,
    const pthread_mutexattr_t *attributes);
int checked_pthread_mutex_destroy(pthread_mutex_t *mutex);
int checked_pthread_mutex_lock(pthread_mutex_t *mutex);
int checked_pthread_mutex_unlock(pthread_mutex_t *mutex);

int checked_pthread_cond_init(
    pthread_cond_t *condition,
    const pthread_condattr_t *attributes);
int checked_pthread_cond_destroy(pthread_cond_t *condition);
int checked_pthread_cond_wait(
    pthread_cond_t *condition,
    pthread_mutex_t *mutex);
int checked_pthread_cond_signal(pthread_cond_t *condition);
int checked_pthread_cond_broadcast(pthread_cond_t *condition);

#endif
