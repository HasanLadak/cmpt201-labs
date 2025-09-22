#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char input[256];
  while (1) {
    printf("Enter programs to run.\n");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) == 0) {
      continue;
    }
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork failed");
      continue;
    }
    if (pid == 0) {
      execl(input, input, NULL);
      perror("Exec failure");
      exit(1);
    } else {
      int status;
      waitpid(pid, &status, 0);
    }
  }
  return 0;
}
