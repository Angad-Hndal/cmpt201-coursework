#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char line[1024];

  printf("Enter programs to run.\n");

  for (;;) {
    printf("> ");
    fflush(stdout);

    if (fgets(line, sizeof(line), stdin) == NULL) {
      putchar('\n'); // handle Ctrl+D cleanly
      break;
    }

    pid_t pid = fork();
    if (pid == 0) {
      // child
      execl(line, line, (char *)NULL);
      perror("Exec failure");
      _exit(127);
    } else if (pid > 0) {
      // parent
      waitpid(pid, NULL, 0);
    } else {
      perror("fork");
    }
  }

  return 0;
}
