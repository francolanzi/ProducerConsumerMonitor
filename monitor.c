#include <pthread.h>
#include "monitor.h"

void init_monitor(monitor_t *monitor) {
  monitor->count = 0;
  buffer_init(&monitor->buffer);
  pthread_cond_init(&monitor->empty, NULL);
  pthread_cond_init(&monitor->full, NULL);
  pthread_mutex_init(&monitor->mutex, NULL);
}

void destroy_monitor(monitor_t *monitor) {
  pthread_cond_destroy(&monitor->empty);
  pthread_cond_destroy(&monitor->full);
  pthread_mutex_destroy(&monitor->mutex);
}

void insertion(monitor_t *monitor, int value) {
  pthread_mutex_lock(&monitor->mutex);
  if (monitor->count == BUFF_SIZE) {
    pthread_cond_wait(&monitor->full, &monitor->mutex);
  }
  buffer_insert(&monitor->buffer, value);
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
  int value = buffer_remove(&monitor->buffer);
  monitor->count--;
  if (monitor->count == BUFF_SIZE - 1) {
    pthread_cond_signal(&monitor->full);
  }
  pthread_mutex_unlock(&monitor->mutex);
  return value;
}