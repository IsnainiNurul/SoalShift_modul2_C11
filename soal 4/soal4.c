#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/sysmacros.h>
int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  int inc=1;

  while(1) {
   char makanEnak[]="/home/galihpribadi04/Documents/makanan/makan_enak.txt";
   struct stat info;
   stat(makanEnak,&info);
   time_t now;
   time(&now);
   int rentang;

   rentang = difftime(now, info.st_atime);
   if(rentang<=30){
     char path[150],str[20];
     strcpy(path, "/home/galihpribadi04/Documents/makanan/makan_sehat");
     sprintf(str,"%d.txt",inc);
     strcat(path,str);
     FILE *baru;
     baru = fopen(path,"w");
     fclose(baru);
     inc++;

     sleep(5);
     }
  }
  exit(EXIT_SUCCESS);
}
