#include "buffer.h"

void buffer_init(buffer_t *buffer) {
  buffer->last = 0;
}

void buffer_insert(buffer_t *buffer, int value) {
  buffer->values[buffer->last++] = value;
}

int buffer_remove(buffer_t *buffer) {
  int elem = buffer->values[0];
  buffer->last--;
  for(int i = 0; i < buffer->last; i++) {
    buffer->values[i] = buffer->values[i + 1];
  }
  return elem;
}