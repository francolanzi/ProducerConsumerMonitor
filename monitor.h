typedef struct {
  pthread_cond_t empty;
  pthread_cond_t full;
  pthread_mutex_t mutex;
  int count;
} monitor_t;

void init_monitor(monitor_t *monitor);
void destroy_monitor(monitor_t *monitor);
void insertion(monitor_t *monitor, int elem);
int removal(monitor_t *monitor);