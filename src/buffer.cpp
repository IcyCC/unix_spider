//
// Created by 苏畅 on 2019/1/14.
//

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "buffer.h"

buffer_item *buffer;

sem_t sem_empty;
sem_t sem_full;
pthread_mutex_t mutex;
int count;

int Initialize() {
    sem_init(&sem_empty, 0, BUFFER_SIZE-1);
    sem_init(&sem_full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    count = 0;
    buffer = (buffer_item*) malloc (sizeof(buffer_item) * BUFFER_SIZE);

    return 0;
}

int Deinitialize() {
    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);
    pthread_mutex_destroy(&mutex);
    free(buffer);

    return 0;
}

int InsertItem(buffer_item item) {
    /* insert item into buffer
     * return 0 if successful, otherwise
     * return -1 indicating an error condition
     */

    // Acquire the empty semaphore and descrease the count
    sem_wait(&sem_empty);

    // Acquire mutex lock
    pthread_mutex_lock(&mutex);

    // Insert item into buffer
    buffer[count++] = item;

    // Release mutex lock
    pthread_mutex_unlock(&mutex);

    // Post the full semaphore and increase the count
    sem_post(&sem_full);

    return 0;
}

int RemoveItem(buffer_item *item) {
    /* remove an object from buffer
     * placing it in item
     * return 0 if successful, otherwise
     * return -1 indicating an error condition
     */

    // Acquire the full semaphore and decrease the count
    sem_wait(&sem_full);

    // Acquire mutex lock
    pthread_mutex_lock(&mutex);

    // Remove object from buffer placing it in item
    *item = buffer[--count];

    // Release mutex lock
    pthread_mutex_unlock(&mutex);

    // Post the empty semaphore and increase the count
    sem_post(&sem_empty);

    return 0;
}