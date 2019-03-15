#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <signal.h>

int main() {
  //Program untuk kill proses agar proses tidak berjalan terus
  char bunuh[10] = {"soal5a"};

  char *argv[3] = {"killall", bunuh, NULL};
  execv("/usr/bin/killall", argv);

  return 0;
}
