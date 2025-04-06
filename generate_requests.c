#include "producer_consumer.h"

//produce items and place in buffer
//modify code below to synchronize correctly

//lock and conditions
pthread_mutex_t lock;
pthread_cond_t empty;
pthread_cond_t full;
//used to make sure producer doesnt overwrite un consumed data or consumer doesnt reconsume data
int count = 0;

//method to produce/consume data
void *generate_requests_loop(void *data)
{
    int thread_id = *((int *)data);
    while(1) {
        //aquire lock
        pthread_mutex_lock(&lock);
        //If producer
        if (thread_id < num_producers) {
            //Produced all items
            if(item_to_produce >= total_items) {
                //release lock
                pthread_mutex_unlock(&lock);
                break;
            }
            //if the buffer is full
            while(count == max_buf_size) {
                //wait for signal
                pthread_cond_wait(&full, &lock);
            }
            //produce item in buffer
            buffer[producer_index] = item_to_produce++;
            //print method for producing
            print_produced(buffer[producer_index], thread_id);
            //adjust the index the producers at
            producer_index = (producer_index + 1) % max_buf_size;
            //increment amount of items available to consume
            count++;
            //send signal to consumer
            pthread_cond_signal(&empty);
        }
        //Consumer
        else {
            //if you consumed all the items
            if(item_to_consume >= total_items) {
                //release lock
                pthread_mutex_unlock(&lock);
                break;
            }
            //nothing to consume and and not all items were produced yet
            while(count == 0 && item_to_produce < total_items) {
                pthread_cond_wait(&empty, &lock);
            }
            //if theres nothing to consume and everything is finished consuming
            if(count == 0 && item_to_produce >= total_items) {
                pthread_mutex_unlock(&lock);
                break;
            }
            //store the value to consume
            int consume_value = buffer[consumer_index];
            //print method for cosuming
            print_consumed(consume_value, thread_id);
            //adjust index of the consumer pointer
            consumer_index = (consumer_index + 1) % max_buf_size;
            //decrement amount of items available to consume
            count--;
            item_to_consume++;
            //send signal to producer that the buffer isnt full anymore
            pthread_cond_signal(&full);
        }
        //unlock when finished
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}