#define BUFF_SIZE 255

typedef struct {
  int values[BUFF_SIZE];
  int last;
} buffer_t;

void buffer_init(buffer_t *buffer);
void buffer_insert(buffer_t *buffer, int value);
int buffer_remove(buffer_t *buffer);