#include "xerrori.h"
#define buf_size 20
#define QUI __LINE__,__FILE__
// c <= p <= c + buf_size

typedef struct
{
    char *file_in;//
    pthread_mutex_t *m_buffer_index;//
    int *buffer;//
    int buf_index;//
    sem_t *sem_free_slots;//
    sem_t *sem_data_items;//
    int readed_files;
    pthread_t thread;
} ProducerData;


typedef struct
{
    FILE *file_out;//
    pthread_mutex_t *m_buffer_index;//
    int *buffer;//
    int buf_index;//
    sem_t *sem_free_slots;//
    sem_t *sem_data_items;//
    pthread_mutex_t *m_file_out;//
    int readed_files;
    pthread_t thread;
} ConsumerData;

/*
    PRODUCER
*/
void *write_positive_numbers(void *arg)
{
    ProducerData *producer_data = (ProducerData*) arg;
    FILE *file_in = fopen(producer_data->file_in, "r");
    if (file_in == NULL) 
    {
        perror("Errore apertura file"); 
        pthread_exit(NULL); /**/
    }
    int x;
    while (fscanf(file_in, "%d", &x) == 1) 
    {
        if (x > 0) 
        {
            xsem_wait(producer_data->sem_free_slots,QUI);
            xpthread_mutex_lock(producer_data->m_buffer_index, QUI);
            int index = producer_data->buf_index % buf_size;
            producer_data->buffer[index] = x;
            *(producer_data->buf_index)++;
            xpthread_mutex_unlock(producer_data->m_buffer_index, QUI);
            xsem_post(producer_data->sem_data_items,QUI);
        }   
    }
    fclose(file_in);
    pthread_exit(NULL); 
}
/**
    CONSUMER
*/
void write_file_out(void *arg)
{

    ConsumerData *consumer_data = (ConsumerData*) arg;
    // !! da interrompere quando i produttori hanno finito !!
    int n;
    while(n!=-1) {
        xsem_wait(consumer_data->sem_data_items, QUI);
        xpthread_mutex_lock(consumer_data->m_buffer_index, QUI);
        int element = buffer[*(consumer_data->buffer_index) % buf_size];
        *(consumer_data->buf_index)++;
        xpthread_mutex_unlock(consumer_data->m_buffer_index, QUI);
        xsem_post(consumer_data->sem_free_slots, QUI);
        
        int dividers_count = get_dividers_count(element);

        xpthread_mutex_lock(consumer_data->m_file_out, QUI);
        fprintf(consumer_data->file_out, "%d %d \n", element, dividers_count);
        xpthread_mutex_unlock(consumer_data->m_file_out, QUI);
    }
}


int get_dividers_count(int n)
{
  assert(n>0);
  int d = 0;
  for (int i=1; i<=n; i ++)
      if(n%i==0) d++;
  return d;
}


int main(int argc, char *argv[]) 
{
    if(argc <= 4) 
    {
        printf("Uso\n\t%s file\n", argv[0]);
        exit(1);
    }
    pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
    int buffer[buf_size];
    int buf_index = 0; 
    int total_producers = argc - 3; 
    int readed_files = 0;
    sem_t sem_free_slots, sem_data_items;
    // 0 -> thread dell stesso processo
    // buf_size -> valore iniziale semaforo 
    xsem_init(&sem_free_slots, 0, buf_size, QUI);
    xsem_init(&sem_data_items, 0, 0, QUI);
    ProducerData producer_data[total_producers];
    for(int i = 1; i <= total_producers; i++) 
    {
        producer_data[i]->file_in = argv[i];
        producer_data[i]->m_buffer_index = &mu;
        producer_data[i]->buffer = &buffer;
        producer_data[i]->buf_index = &buf_index;
        producer_data[i]->sem_free_slots = &sem_free_slots;
        producer_data[i]->sem_data_items = &sem_data_items;
        producer_data[i]->readed_files = &readed_files;
        xpthread_create(
            producer_data[i]->thread,
            NULL,
            write_positive_numbers,
            producer_data+i,
            QUI
        );
    }
    FILE *file_out = fopen(argv[argc-1], "a");
    if(file_out == NULL) {perror("Errore apertura file"); return -1;}
    pthread_mutex_t mu_file_out = PTHREAD_MUTEX_INITIALIZER;
    int total_consumers = argv[argc];
    ConsumerData consumer_data[total_consumers];
    for(int i = 0; i < total_consumers; i++) 
    {
        consumer_data[i]->file_out = file_out;
        consumer_data[i]->m_buffer_index = &mu;
        consumer_data[i]->buffer = &buffer;
        consumer_data[i]->buf_index = &buf_index;
        consumer_data[i]->sem_free_slots = &sem_free_slots;
        consumer_data[i]->sem_data_items = &sem_data_items;
        consumer_data[i]->m_file_out = &mu_file_out;
        consumer_data[i]->readed_files = &readed_files;
        xpthread_create(
            producer_data[i]->thread,
            NULL,
            write_file_out,
            consumer_data+i,
            QUI
        );
    }
    return 0;
}