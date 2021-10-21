#include <pthread.h>
#include "monitor.h"

#define N 100

int buffer[N];
int size = 0;

void insert_elem(int elem) {
  buffer[size++] = elem;
}

int remove_elem() {
  int elem = buffer[0];
  size--;
  for(int i = 0; i < size; i++) {
    buffer[i] = buffer[i + 1];
  }
  return elem;
}

void init_monitor(monitor_t *monitor) {
  monitor->count = 0;
  pthread_cond_init(&monitor->empty, NULL);
  pthread_cond_init(&monitor->full, NULL);
  pthread_mutex_init(&monitor->mutex, NULL);
}

void destroy_monitor(monitor_t *monitor) {
  pthread_cond_destroy(&monitor->empty);
  pthread_cond_destroy(&monitor->full);
  pthread_mutex_destroy(&monitor->mutex);
}

void insertion(monitor_t *monitor, int elem) {
  pthread_mutex_lock(&monitor->mutex);
  if (monitor->count == N) {
    pthread_cond_wait(&monitor->full, &monitor->mutex);
  }
  insert_elem(elem);
  monitor->count++;
  if (monitor->count == 1) {
    pthread_cond_signal(&monitor->empty);
  }
  pthread_mutex_unlock(&monitor->mutex);
}

int removal(monitor_t *monitor) {
  pthread_mutex_lock(&monitor->mutex);
  if (monitor->count == 0) {
    pthread_cond_wait(&monitor->empty, &monitor->mutex);
  }
  int elem = remove_elem();
  monitor->count--;
  if (monitor->count == N - 1) {
    pthread_cond_signal(&monitor->full);
  }
  pthread_mutex_unlock(&monitor->mutex);
  return elem;
}