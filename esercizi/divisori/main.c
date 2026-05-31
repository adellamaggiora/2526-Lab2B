#include "xerrori.h"
#define buf_size 20

// c <= p <= c + buf_size

// struct contenente i parametri di input e output di ogni thread produttore 
typedef struct
{
    char *file_in;
    pthread_mutex_t *m_buffer_index;
    int *buffer;
    int buf_index;
    sem_t *sem_free_slots;
    sem_t *sem_data_items;
    pthread_t thread;
} ProducerData;

// struct contenente i parametri di input e output di ogni thread produttore 
typedef struct
{
    FILE *file_out;
    pthread_mutex_t *m_buffer_index;
    int *buffer;
    int buf_index;
    sem_t *sem_free_slots;
    sem_t *sem_data_items;
    pthread_mutex_t *m_outfile;
    int outfile_line;
    pthread_t thread;
} ConsumerData;


int main(int argc, char *argv[]) 
{
    if(argc <= 4) 
    {
        printf("Uso\n\t%s file\n", argv[0]);
        exit(1);
    }
    pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
    int buffer[buf_size];
    int buf_index=0;  
    sem_t sem_free_slots, sem_data_items;
    xsem_init(&sem_free_slots,0,buf_size,__LINE__,__FILE__);
    xsem_init(&sem_data_items,0,0,__LINE__,__FILE__);
    int total_producers = argc - 3;
    ProducerData producer_data[total_producers];
    for(i = 0; i < total_producers; i++) 
    {
        producer_data[i].file_in = argv[i];
        producer_data[i].m_buffer_index = &mu;
        producer_data[i].buffer = buffer;
        producer_data[i].buf_index = &buf_index;
        producer_data[i].sem_free_slots = &sem_free_slots;
        producer_data[i].sem_data_items = &sem_data_items;
        xpthread_create(producer_data[i].thread,NULL,write_positive_numbers,producer_data+i,__LINE__,__FILE__);
    }
    FILE *file_out = fopen(argv[argc-1]);
    if(file_out == NULL) {perror("Errore apertura file"); return -1;}
    pthread_mutex_t mu_file_out = PTHREAD_MUTEX_INITIALIZER;
    int total_consumers = argv[argc];
    ConsumerData consumer_data[total_consumers];
    outfile_line = 0;
    for(i = 0; i < total_producers; i++) 
    {
        consumer_data[i].file_out = file_out;
        consumer_data[i].m_buffer_index = &mu;
        consumer_data[i].buffer = buffer;
        consumer_data[i].buf_index = &buf_index;
        consumer_data[i].sem_free_slots = &sem_free_slots;
        consumer_data[i].sem_data_items = &sem_data_items;
        consumer_data[i].m_file_out = &mu_file_out;
        consumer_data[i].outfile_line = &outfile_line;
        xpthread_create(producer_data[i].thread,NULL,write_outfile,consumer_data+i,__LINE__,__FILE__);
    }
    return 0;
}