#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  printf("Please enter some text: ");
  nread = getline(&line, &len, stdin);
  if (nread == -1) {
    perror("getline");
    free(line);
    return 1;
  }

  printf("Tokens:\n");
  char *saveptr;
  char *token = strtok_r(line, " \n", &saveptr);

  while (token != NULL) {
    printf("  %s\n", token);
    token = strtok_r(NULL, " \n", &saveptr);
  }

  free(line);
  return 0;
}
