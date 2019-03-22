#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t anak1;
    int pepiku[4];
        	pipe(pepiku); // untuk membuat suatu pipe
        	pipe(pepiku+2);// untuk menambah pipe 
    char rest[2000];
    anak1 = fork();
    if(anak1 == 0)// sebagai child
    {
      execl("/usr/bin/unzip","unzip", "campur2.zip", NULL);// untuk menunzip
    }
	else// sebagai parent
	{
	    	pid_t anak2;
        	int p2;
		while(wait(&status)>0);
       		anak2 = fork();
        	if(anak2==0)//adalah child
		{
			close(pepiku[0]);//read
          		close(pepiku[2]);
			close(pepiku[3]);
          		dup2(pepiku[1], STDOUT_FILENO); //untuk menyimpan hasil ls nya  untuk di write
          		close(pepiku[1]);// setiap dup perlu tanda close untuk ditutup
		char *argv[3] = {"ls", "/home/isnaini/praktikum2/campur2", NULL};
    execv("/bin/ls", argv);
}
		else//adalah parent yang akan membuat anak
		{
    			pid_t anak3;
  	          	anak3 = fork();
	    		if(anak3==0)// ini adalah child
			{
	              		close(pepiku[1]);
	             		dup2(pepiku[0],STDIN_FILENO); //untuk read 
	              		close(pepiku[0]);
	              		close(pepiku[2]);
	              		dup2(pepiku[3],STDOUT_FILENO);//untuk  write (membuat)
	              		close(pepiku[3]);

			char *argv[3] = {"grep",".txt$", NULL};
    execv("/bin/grep", argv);
            		}
			else
			{
              			close(pepiku[1]); 
	             		int cetak = read(pepiku[2],rest,sizeof(rest)); 
              			close(pepiku[2]);
              			FILE* file;
              			file = fopen("daftar.txt","w+");
             			fprintf(file," Berikut Berupa File berformat .txt :\n%.*s\n",cetak,rest);// memasukkan hasil ls grep ke file
             			printf("Berikut Berupa File berformat .txt :\n%.*s\n",cetak,rest);
              			fclose(file);
            	}
        }
    }
}
