#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BLOCKSIZE 128
#define TOTALSIZE 256
#define BUFSIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUFSIZE];
  ssize_t len = snprintf(buf, BUFSIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *space = sbrk(TOTALSIZE);
  struct header *first = (struct header *)space;
  struct header *second = (struct header *)((char *)space + BLOCKSIZE);

  first->size = BLOCKSIZE;
  first->next = NULL;
  second->size = BLOCKSIZE;
  second->next = first;

  print_out("first block:       %p\n", first, sizeof(first));
  print_out("second block:      %p\n", second, sizeof(second));
  print_out("first block size:  %lu\n", &first->size, sizeof(first->size));
  print_out("first block next:  %p\n", &first->next, sizeof(first->next));
  print_out("second block size: %lu\n", &second->size, sizeof(second->size));
  print_out("second block next: %p\n", &second->next, sizeof(second->next));

  char *data_first = (char *)first + sizeof(struct header);
  char *data_second = (char *)second + sizeof(struct header);
  size_t data_bytes = BLOCKSIZE - sizeof(struct header);

  memset(data_first, 0, data_bytes);
  memset(data_second, 1, data_bytes);

  for (size_t i = 0; i < data_bytes; i++)
    print_out("%d\n", &data_first[i], sizeof(char));
  for (size_t i = 0; i < data_bytes; i++)
    print_out("%d\n", &data_second[i], sizeof(char));

  return 0;
}
