#include "producer_consumer.h"

//method to print after producing
void print_produced(int num, int producer) {

    printf("Produced %d by producer thread: %d\n", num, producer);
}
//method to print after consuming
void print_consumed(int num, int consumer) {

    printf("Consumed %d by consumer thread: %d\n", num, consumer);

}
