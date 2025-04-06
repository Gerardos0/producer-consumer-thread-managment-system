#Producer-Consumer System

Multi-threaded implementation of a producer-consumer pattern using POSIX threads, to practice concurrency concepts and synchronization logic.

---

## Project Overview

This system implements:
- Thread managment for data preservation(unread data isnt overwritten and data isnt read twice)
- Synchronization of threads using mutex locks and condition variables
- Circular buffer for FIFO operations.
- Producer/consumer load balancing
- Resource cleanup on exit

---

## Features and Implementation
- **Language**: C
- **Thread API**: POSIX threads (`pthreads`)
- **Data Structures**: Circular buffer with modulo arithmetic
- **Concurrency Control**
  - `pthread_mutex_t lock` to protects shared buffer access
  - `pthread_cond_t empty/full` to coordinate producer-consumer signaling
  - Atomic index management for thread-safe operations

---

## Build & Execution

```sh
# Compile
gcc -pthread master_worker.c -o master-worker

# Run with parameters:
# ./master-worker [total_items] [max_buf_size] [num_workers] [num_masters]
./master-worker 10 8 4 3
