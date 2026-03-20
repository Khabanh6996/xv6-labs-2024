#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(2, "Usage: xargs <command> [args...]\n");
    exit(1);
  }

  char *command = argv[1];
  char *cmd_args[MAXARG];
  char buf[512];
  int n;

  for (int i = 1; i < argc; i++) {
    cmd_args[i - 1] = argv[i];
  }

  while (1) {
    int i = 0;
    while ((n = read(0, &buf[i], 1)) > 0) {
      if (buf[i] == '\n') break;
      i++;
    }

    if (n <= 0 && i == 0) break;

    buf[i] = '\0';
    cmd_args[argc - 1] = buf;
    cmd_args[argc] = 0;

    if (fork() == 0) {
      exec(command, cmd_args);
      fprintf(2, "xargs: exec %s failed\n", command);
      exit(1);
    } else {
      wait(0);
    }
  }

  exit(0);
}