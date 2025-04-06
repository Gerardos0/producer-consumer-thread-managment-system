#ifndef PROD_CONS_H
#define PROD_CONS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>

// Shared global variables
extern int item_to_produce, item_to_consume;
extern int producer_index, consumer_index;
extern int total_items, max_buf_size, num_consumers, num_producers;
extern int *buffer;

// Synchronization primitives
extern pthread_mutex_t lock;
extern pthread_cond_t empty;
extern pthread_cond_t full;

// Function declarations
void print_produced(int num, int producer);
void print_consumed(int num, int consumer);
void *generate_requests_loop(void *data);

#endif // PROD_CONS_H