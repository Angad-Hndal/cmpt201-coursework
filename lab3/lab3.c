#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> //ssize_t

#define CAP 5

int main(void) {
  char *hist[CAP] = {0};
  int count = 0, start = 0;

  char *buf = NULL;
  size_t cap = 0;
  ssize_t n;

  for (;;) {
    printf("Enter input: ");
    fflush(stdout);
    n = getline(&buf, &cap, stdin);
    if (n == -1)
      break;

    if (n > 0 && buf[n - 1] == '\n')
      buf[n - 1] = '\0';

    int idx;
    if (count < CAP) {
      idx = (start + count) % CAP;
      count++;
    } else {
      idx = start;
      free(hist[idx]);
      start = (start + 1) % CAP;
    }
    hist[idx] = strdup(buf);

    if (strcmp(buf, "print") == 0) {
      for (int i = 0; i < count; i++) {
        int j = (start + i) % CAP;
        printf("%s\n", hist[j]);
      }
    }
  }

  free(buf);
  for (int i = 0; i < CAP; i++)
    free(hist[i]);
  return 0;
}
