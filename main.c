#include "producer_consumer.h"

//variable used in producing/consuming
int item_to_produce, item_to_consume, producer_index, consumer_index;
//variables to store input
int total_items, max_buf_size, num_consumers, num_producers;

int *buffer;


int main(int argc, char *argv[])
{
    //set up array for producers and consumers thread ids
    int *producer_thread_id;
    int *consumer_thread_id;
    //set up array for producers and consumers threads
    pthread_t *producer_thread;
    pthread_t *consumer_thread;
    //set number of items to consume and produce
    item_to_produce = 0;
    item_to_consume = 0;
    //set pointers for consuming and producing
    producer_index = 0;
    consumer_index = 0;
    int i;
    //if not all inputs were given
    if (argc < 5) {
        printf("insufficient args, try again with 4 args 1) total items 2) max buffer size 3) number of producer threads 4) number of consumer threads\n");
        exit(1);
    }
    //save values for inputs
    else {
        total_items = atoi(argv[1]);
        max_buf_size = atoi(argv[2]);
        num_consumers = atoi(argv[3]);
        num_producers = atoi(argv[4]);
    }
    //if buffer size is 0 print
    if(max_buf_size == 0){
        printf("buffer size is 0 so nothing can be processed\n");
        return 0;
    }
    //if total items is 0 print
    if(total_items == 0){
        printf("There are no items to process\n");
        return 0;
    }
    //allocate memory for the buffer
    buffer = (int *)calloc (sizeof(int), max_buf_size);
    //initialize the lock and make sure it didnt fail
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("mutex_lock couldn't initialize");
        exit(1);
    }

    //create producer threads---------------------------------------------------------------------------
    //allocate memory for the threads array and threads id array
    producer_thread_id = (int *)malloc(sizeof(int) * num_producers);
    producer_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_producers);
    //set values in thread id array
    for (i = 0; i < num_producers; i++)
        producer_thread_id[i] = i;
    //create threads and store in threads array
    for (i = 0; i < num_producers; i++)
        pthread_create(&producer_thread[i], NULL, generate_requests_loop, (void *)&producer_thread_id[i]);

    //create consumer threads----------------------------------------------------------------------------
    //allocate memory for the threads array and threads id array
    consumer_thread_id = (int *)malloc(sizeof(int) * num_consumers);
    consumer_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_consumers);
    //set values in thread id array
    for (i = 0; i < num_consumers; i++)
        consumer_thread_id[i] = num_producers + i;
    //create threads and store in threads array
    for (i = 0; i < num_consumers; i++)
        pthread_create(&consumer_thread[i], NULL, generate_requests_loop, (void *)&consumer_thread_id[i]);

    //wait for all threads to complete---------------------------------------------------------------------------
    //join threads so they wait for other threads to finish
    for (i = 0; i < num_producers; i++)
    {
        pthread_join(producer_thread[i], NULL);
        printf("producer %d joined\n", i);
    }
    for (i = 0; i < num_consumers; i++)
    {
        pthread_join(consumer_thread[i], NULL);
        printf("consumer %d joined\n", consumer_thread_id[i]);
    }
    /*----Deallocating Buffers---------------------*/
    free(buffer);
    free(producer_thread_id);
    free(producer_thread);

    return 0;
}
