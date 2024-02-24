#ifndef __ASYNC__
#define __ASYNC__

#include <pthread.h>

typedef struct my_item {
  int client_socket_fd;
  struct my_item *next;
  struct my_item *prev;
} my_item_t;

typedef struct my_queue {
  int size;
  my_item_t *head;
} my_queue_t;

my_queue_t queue_work;

void my_init(my_queue_t *my_queue);
void my_push(my_queue_t *my_queue, int client_socket_fd);
int my_pop(my_queue_t *my_queue);

void async_init(int);
void async_run(void (*fx)(int), int args);

#endif
