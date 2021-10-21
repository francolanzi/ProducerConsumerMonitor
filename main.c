#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "monitor.h"
#include <string.h>

#define MAX 1000

int produce() {
  sleep(1);
  return rand() % 10;
}

void consume(int elem) {
  sleep(1);
  printf("%d ", elem);
  fflush(stdout);
}

void *producer(void *arg) {
  monitor_t *monitor = (monitor_t *) arg;
  for (int i = 0; i < MAX; i++) {
    int elem = produce();
    insertion(monitor, elem);
  }
  pthread_exit(NULL);
}

void *consumer(void *arg) {
  monitor_t *monitor = (monitor_t *) arg;
  for (int i = 0; i < MAX; i++) {
    int elem = removal(monitor);
    consume(elem);
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t pro, con;
  monitor_t monitor;
  srand(time(NULL));
  init_monitor(&monitor);
  pthread_create(&pro, NULL, &producer, (void *) &monitor);
  pthread_create(&con, NULL, &consumer, (void *) &monitor);
  pthread_join(pro, NULL);
  pthread_join(con, NULL);
  destroy_monitor(&monitor);
}