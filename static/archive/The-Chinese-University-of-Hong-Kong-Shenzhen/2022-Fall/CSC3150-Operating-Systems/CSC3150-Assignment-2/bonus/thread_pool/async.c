#include <stdlib.h>
#include <pthread.h>
#include "async.h"
#include "utlist.h"
// #include <stdio.h>

int works;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_begin = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_end = PTHREAD_COND_INITIALIZER;

// perform a casual "init" action from the queue (initialize)
void my_init(my_queue_t *my_queue){
    my_queue -> head = NULL;
    my_queue -> size = 0;
}
// perform a casual "push" action from the queue (add item)
void my_push(my_queue_t *my_queue, int client_socket_fd){
    my_item_t *my_item = calloc(1, sizeof(my_item_t));
    my_item -> client_socket_fd = client_socket_fd;

    pthread_mutex_lock(&mutex);

    DL_APPEND(my_queue -> head, my_item);
    my_queue -> size++;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}
// perform a casual "pop" action from the queue (remove item)
int my_pop(my_queue_t *my_queue){
    pthread_mutex_lock(&mutex);

    while(!my_queue -> size){
        pthread_cond_wait(&cond, &mutex);
    }
    my_item_t *my_item = my_queue -> head;
    int client_socket_fd = my_queue -> head -> client_socket_fd;
    my_queue -> size--;
    DL_DELETE(my_queue -> head, my_queue -> head);
    pthread_mutex_unlock(&mutex);

    free(my_item);
    return client_socket_fd;
}

void *thread_pool(void *unused){
    while(1){
        pthread_mutex_lock(&mutex);

        if(works == 0) break;
        
        pthread_cond_wait(&cond_begin, &mutex);

        my_pop(&queue_work);
        works--;

        pthread_cond_signal(&cond_end);
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_exit(NULL);
}

void async_init(int num_threads) {
    /** TODO: create num_threads threads and initialize the thread pool **/
    if(num_threads > 0) {
        pthread_t *threads = (pthread_t *) malloc(sizeof(pthread_t)*num_threads);
        pthread_t *p = threads;
        my_init(&queue_work);

        // create num_threads threads + thread pool
        for(int i = 0; i < num_threads; i++, p++) {
            pthread_create(p, NULL, thread_pool, NULL);
        }
    }

    return;
}

void async_run(void (*handler)(int), int args) {
    /** TODO: rewrite it to support thread pool **/
    pthread_mutex_lock(&mutex);
    while(works > 0)
        pthread_cond_wait(&cond_end, &mutex);
    works++;
    my_push(&queue_work, args);
    handler(args);
    pthread_cond_signal(&cond_begin);
    pthread_mutex_unlock(&mutex);

    return;
}