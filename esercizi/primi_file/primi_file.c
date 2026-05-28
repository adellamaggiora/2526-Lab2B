#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>à
#include <semaphore.h>

pthread_mutex_t mutex; //per accesso in sezione critica in mutua esclusione
//pthread_mutex_lock(&m);
//pthread_mutex_unlock(&m);

//sem_t s; 
//sem_wait(&s);
//sem_post(&s);

int *read_numbers(char *file_name) {
    FILE *file = fopen(file_name, "r");
    int *result = NULL;
    int line_number = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while((read = getline(line, &len, file)) != -1) {
        result = realloc(result, (line_number + 1) * sizeof(int));
        result[line_number] = atoi(line);
    }
    // *line, &line, line
    return result;
}

int count_prime_numbers() {

}

int main(int argc, char *argv[]) {
    char *file_name = argv[1];
    int *numbers = read_numbers(file_name);
    return 0;
}

