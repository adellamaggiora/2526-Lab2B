#include "xerrori.h"
#define buf_size 20
#define QUI __LINE__,__FILE__
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
    pthread_mutex_t *m_file_out;
    int outfile_line;
    pthread_t thread;
} ConsumerData;

//prende degli interi positivi da un file e gli carica in mutua esclusione su un buffer 
void *write_positive_numbers(void *arg)
{
    // verifico se sem_free_slots = 0, se si vo in attesa
    // sia sem_free_slots = n, con n != 0 
    // fo la fscan del file -> prendo n dati -> prendo solo i positivi (il tutto avviene in parallelo)
    // e li metto in un array positives

    // in un ciclo ad positives.length eseguo questi passi:
    // 1. prendo il mutex sull'indice del buffer
    // 2. ci metto il dato 
    // 3. incremento p_index (l'indice del produttore)
    // 4. rilascio il mutex

    // WARNING: l'invariante secondo cui, quando il consumatore accede a un indice, trova SEMPRE il dato,
    // non viene rispettata, un consumatore potrebbe trovare un dato nullo e restituire SIGFAULT
    ProducerData *producer_data = (ProducerData*) arg;
    FILE *file_in = fopen(producer_data->file_in, "r");
    if (file_in == NULL) {perror("Errore apertura file"); return -1;}
    xsem_wait(producer_data->sem_free_slots,QUI);
    xpthread_mutex_lock(producer_data->m_buffer_index, QUI);
    int free_slots = -1;
    sem_getvalue(producer_data->sem_free_slots, &free_slots);
    bool positive_found = false;
    int x;
    while (fscanf(file_in, "%d", &x) == 1) 
    {
        if (x > 0) 
        {
            positive_found = true;
            if(free_slots == 0){break;}
            int index = producer_data->buf_index;
            producer_data->buffer[index];
            producer_data->buf_index++;
            free_slots--;
            xsem_wait(producer_data->sem_free_slots,QUI);
            xsem_post(producer_data->sem_data_items,QUI);
        }   
    }
    if(positive_found == false) 
    {
        xsem_post(producer_data->sem_free_slots,QUI);
    }
    xpthread_mutex_unlock(producer_data->m_buffer_index, QUI);
}

write_outfile()
{

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
    int buf_index=0;  
    sem_t sem_free_slots, sem_data_items;
    xsem_init(&sem_free_slots,0,buf_size,QUI);
    xsem_init(&sem_data_items,0,0,QUI);
    int total_producers = argc - 3;
    ProducerData producer_data[total_producers];
    for(int i = 1; i <= total_producers; i++) 
    {
        producer_data[i].file_in = argv[i];
        producer_data[i].m_buffer_index = &mu;
        producer_data[i].buffer = buffer;
        producer_data[i].buf_index = &buf_index;
        producer_data[i].sem_free_slots = &sem_free_slots;
        producer_data[i].sem_data_items = &sem_data_items;
        xpthread_create(producer_data[i].thread,NULL,write_positive_numbers,producer_data+i,QUI);
    }
    FILE *file_out = fopen(argv[argc-1], "r");
    if(file_out == NULL) {perror("Errore apertura file"); return -1;}
    pthread_mutex_t mu_file_out = PTHREAD_MUTEX_INITIALIZER;
    int total_consumers = argv[argc];
    ConsumerData consumer_data[total_consumers];
    int outfile_line = 0;
    for(int i = 0; i < total_producers; i++) 
    {
        consumer_data[i].file_out = file_out;
        consumer_data[i].m_buffer_index = &mu;
        consumer_data[i].buffer = buffer;
        consumer_data[i].buf_index = &buf_index;
        consumer_data[i].sem_free_slots = &sem_free_slots;
        consumer_data[i].sem_data_items = &sem_data_items;
        consumer_data[i].file_out = &mu_file_out;
        consumer_data[i].outfile_line = &outfile_line;
        xpthread_create(producer_data[i].thread,NULL,write_outfile,consumer_data+i,QUI);
    }
    return 0;
}