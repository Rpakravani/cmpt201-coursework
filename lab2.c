#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  printf("Enter program to run.\n");

  while (1) {
    printf("> ");
    fflush(stdout);

    nread = getline(&line, &len, stdin);
    if (nread == -1) {
      free(line);
      break;
    }
    if (nread > 0 && line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
    }

    pid_t pid = fork();
    if (pid == 0) {

      execlp(line, line, (char *)NULL);

      perror("Exec failure");
      _exit(1);
    } else {
      int status;
      if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
      }
    }
  }
}
