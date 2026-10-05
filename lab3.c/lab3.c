#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HISTORY_SIZE 5

void store_line(char **history, int count, char *line) {
  int slot = count % HISTORY_SIZE;
  if (count >= HISTORY_SIZE) {
    free(history[slot]);
  }
  history[slot] = line;
}

void print_history(char **history, int count) {
  int start = (count < HISTORY_SIZE) ? 0 : count % HISTORY_SIZE;
  int n = (count < HISTORY_SIZE) ? count : HISTORY_SIZE;
  for (int i = 0; i < n; i++) {
    int idx = (start + i) % HISTORY_SIZE;
    printf("%s", history[idx]);
  }
}

int main(void) {
  char *history[HISTORY_SIZE] = {NULL};
  int count = 0;
  char *line = NULL;
  size_t cap = 0;
  ssize_t nread;

  while (1) {
    printf("Enter input: ");
    fflush(stdout);

    nread = getline(&line, &cap, stdin);
    if (nread == -1) {
      break;
    }

    int is_print = (strcmp(line, "print\n") == 0);
    if (is_print) {
      print_history(history, count);
    }

    store_line(history, count, line);
    count++;

    line = NULL;
    cap = 0;
  }

  int n = (count < HISTORY_SIZE) ? count : HISTORY_SIZE;
  for (int i = 0; i < n; i++) {
    free(history[i]);
  }

  free(line);
  return 0;
}
