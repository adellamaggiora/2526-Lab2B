#include "error-manager.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>


/*
    **************************************************
    wrapper per gestione sicura della memroia e thread

    ***************************************************
*/

static void terminate_pthread_error(int error_code, const char *message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(error_code));
    exit(EXIT_FAILURE);
}

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

// int checked_pthread_create(
//     pthread_t *thread,
//     const pthread_attr_t *attributes,
//     void *(*start_routine)(void *),
//     void *argument)
// {
//     int error = pthread_create(thread, attributes, start_routine, argument);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_create failed");

//     return error;
// }

// int checked_pthread_join(pthread_t thread, void **return_value)
// {
//     int error = pthread_join(thread, return_value);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_join failed");

//     return error;
// }

// int checked_pthread_mutex_init(
//     pthread_mutex_t *mutex,
//     const pthread_mutexattr_t *attributes)
// {
//     int error = pthread_mutex_init(mutex, attributes);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_mutex_init failed");

//     return error;
// }

// int checked_pthread_mutex_destroy(pthread_mutex_t *mutex)
// {
//     int error = pthread_mutex_destroy(mutex);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_mutex_destroy failed");

//     return error;
// }

// int checked_pthread_mutex_lock(pthread_mutex_t *mutex)
// {
//     int error = pthread_mutex_lock(mutex);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_mutex_lock failed");

//     return error;
// }

// int checked_pthread_mutex_unlock(pthread_mutex_t *mutex)
// {
//     int error = pthread_mutex_unlock(mutex);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_mutex_unlock failed");

//     return error;
// }

// int checked_pthread_cond_init(
//     pthread_cond_t *condition,
//     const pthread_condattr_t *attributes)
// {
//     int error = pthread_cond_init(condition, attributes);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_cond_init failed");

//     return error;
// }

// int checked_pthread_cond_destroy(pthread_cond_t *condition)
// {
//     int error = pthread_cond_destroy(condition);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_cond_destroy failed");

//     return error;
// }

// int checked_pthread_cond_wait(
//     pthread_cond_t *condition,
//     pthread_mutex_t *mutex)
// {
//     int error = pthread_cond_wait(condition, mutex);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_cond_wait failed");

//     return error;
// }

// int checked_pthread_cond_signal(pthread_cond_t *condition)
// {
//     int error = pthread_cond_signal(condition);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_cond_signal failed");

//     return error;
// }

// int checked_pthread_cond_broadcast(pthread_cond_t *condition)
// {
//     int error = pthread_cond_broadcast(condition);
//     if (error != 0)
//         terminate_pthread_error(error, "pthread_cond_broadcast failed");

//     return error;
// }
