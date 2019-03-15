#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main() {
  pid_t pid, sid;
  pid = fork();
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  umask(0);
  sid = setsid();
  if (sid < 0) 
    {
      exit(EXIT_FAILURE);
    }
  if ((chdir("/home/isnaini/Documents/")) < 0) 
    {
      exit(EXIT_FAILURE);
    }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) 
    {
      DIR *directory;
      if (directory=opendir ("/home/isnaini/Documents"))
        {
	        struct dirent *infolder;
          while ((infolder = readdir(directory)) != NULL)
          {
	        char Filename[1024];
	        int panjang = (int) strlen(infolder->d_name);
	        char *name = infolder->d_name;
	        if(name[panjang-4] == '.' && name[panjang-3] == 'p' && name[panjang-2] == 'n' && name[panjang-1] == 'g')
		      {
		        strcpy(Filename, "gambar/");
		        strcat(Filename, name);
		        panjang = (int)strlen(Filename);
		        Filename[panjang-4] = '\0';
		        strcat(Filename, "_grey.png");
		        char *move[4] = {"mv", name, Filename, NULL};
		        execv("/bin/mv", move);
	        }
        }
      closedir(directory);
    }
  sleep(10);
  }
  exit(EXIT_SUCCESS);
}
