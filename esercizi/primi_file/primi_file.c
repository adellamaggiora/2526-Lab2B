#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>à
#include <semaphore.h>

int *buffer = NULL; 
int buffer_index = 0;
int prime_counter = 0;
int buffer_size = 0;
pthread_mutex_t mutex_buffer;//per accesso al buffer e all'indice

typedef struct {
    int *numbers;
    int length;
} BufferInfo;

BufferInfo read_numbers(char *file_name) {
    FILE *file = fopen(file_name, "r");

    BufferInfo info;
    info.numbers = NULL;
    info.length = 0;

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        info.numbers = realloc(info.numbers, (info.length + 1) * sizeof(int));
        info.numbers[info.length] = atoi(line);
        info.length++;
    }

    free(line);
    fclose(file);

    return info;
}

int count_prime_numbers() {
    while(buffer_index < buffer_size){
        pthread_mutex_lock(&mutex_buffer);
        int number = buffer[buffer_index];
        buffer_index++;
        pthread_mutex_unlock(&mutex_buffer);
        
        if(is_prime(number)) {
            prime_counter++;
        }  
    }

}

int is_prime(int n) {
    if (n < 2) return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    char *file_name = argv[1];
    BufferInfo buffer_info = read_numbers(file_name);
    buffer = buffer_info.numbers;
    buffer_size = buffer_info.length;
    
    pthread_t p1, p2;
    pthread_create(&p1, NULL, count_prime_numbers, NULL);
    pthread_create(&p2, NULL, count_prime_numbers, NULL);
    pthread_join(&p1, NULL);
    pthread_join(&p2, NULL);
    printf("total:%d", prime_counter);
    return 0;
}

