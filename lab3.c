#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 5

int main() {
  char *history[MAX_HISTORY] = {NULL};
  int count = 0;
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter input: ");
    ssize_t read = getline(&line, &len, stdin);
    if (read == -1) {
      break;
    }

    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }

    int index = count % MAX_HISTORY;
    if (history[index] != NULL) {
      free(history[index]);
    }

    history[index] = strdup(line);
    count++;

    if (strcmp(line, "print") == 0) {
      int numToPrint;
      if (count < MAX_HISTORY) {
        numToPrint = count;
      } else {
        numToPrint = MAX_HISTORY;
      }

      int start = count - numToPrint;
      for (int i = start; i < count; i++) {
        int pos = i % MAX_HISTORY;
        printf("%s\n", history[pos]);
      }
    }
  }

  for (int i = 0; i < MAX_HISTORY; i++) {
    if (history[i] != NULL) {
      free(history[i]);
    }
  }
  free(line);

  return 0;
}
