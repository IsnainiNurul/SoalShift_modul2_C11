# SoalShift_modul2_C11

SoalShift modul2 Sistem Operasi kelas C

Isnaini Nurul KurniaSari (05111740000010)

Argo Galih Pribadi       (05111740000150)


**SOAL NO 1**


Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

**Jawab:**


Dikarenakan terdapat aturan tidak boleh menggunakan crontab, maka kita menggunakan daemon hal ini dikarenakan perintah daemon agar file yang berekstensi .png dapat dipindahkan secara realtime atau periodik dan berjalan di belakang layar pada suatu folder ke /home/user/modul2/gambar. Daemon juga dapat membuat suatu aplikasi yang berjalan di sevice berjalan secara otomatis, daemon tidak memiliki parent proses ID.

**Source Code :**
```
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
  if ((chdir("/home/isnaini/modul2")) < 0) 
    {
      exit(EXIT_FAILURE);
    }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1)
    {
      DIR *directory;
      if (directory=opendir ("/home/isnaini/modul2/")) 
      // mengubah direktori ke suatu path secara khusus, fungsi untuk membuka direktori handle gambar dan akan menjalankan 
      perintah pada gambar yang akan dipindah dan akan membuka pada direktori home/isnaini/modul2
      {
      struct dirent *infolder;
      while ((infolder = readdir(directory)) != NULL) // untuk mengecek isi di dalam folder sehingga dapat menjalankan perintah
      selanjutnya
      {
	char Filename[1024];
	int panjang = (int) strlen(infolder->d_name);// panjang karakter sejumlah berapa
	char *name = infolder->d_name;
	if(name[panjang-4] == '.' && name[panjang-3] == 'p' && name[panjang-2] == 'n' && name[panjang-1] == 'g')// perintah yang berfungsi untuk menampung panjang karakter dari nama gambar tanpa ekstensi .png dan akan mereset serta membuat agar kondisi awal dari array tidak berisi.
	{
	  strcpy(Filename, "gambar/");// untuk mencopy
	  strcat(Filename, name);// untuk menampung filename yang telah disimpan
	  panjang = (int)strlen(Filename);
	  Filename[panjang-4] = '\0';
	  strcat(Filename, "_grey.png");// menambah karakter pada suatu ekstensi yang berbasis .png
	  if(fork()==0)
	   {
	    char *move[4] = {"mv", name, Filename, NULL};
	    execv("/bin/mv", move);
	   }
	  }
        }
      closedir(directory);
    }
  sleep(10);
  }
  exit(EXIT_SUCCESS);
}

```
**Penjelasan: **

- ``DIR *directory``; adalah suatu variable dengan nama folder yang menggunakan tipe data DIR.Jika digunakan tanpa parameter, perintah ini dapat menampilkan daftar berkas-berkas dan subdirektori yang terdapat di dalam direktori aktif. Berkas ini memiliki satu parameter, yakni lokasi direktori di mana hendak menampilkan daftar isi direktori. 


- ``struct dirent *infolder``; Struct adalah tipe data bentukan yang berisi kumpulan variabel-variabel yang berada dalam satu nama yang sama dan memiliki kaitan satu sama lain. Berbeda dengan array hanya berupa kumpulan variabel yang bertipe data sama, struct bisa memiliki variabel-variabel yang bertipe data sama atau berbeda, bahkan bisa menyimpan variabel yang bertipe data array atau struct itu sendiri. Variabel-variabel yang menjadi anggota struct disebut dengan elemen struct.


- ``chdir("/home/isnaini/modul2)``; akan mengubah direktori ke suatu path secara khusus 


- ``directory=opendir ("/home/isnaini/modul2/")``;adalah fungsi untuk membuka direktori handle gambar yaitu direktori asal dan akan menjalankan perintah pada gambar yang akan di pindah akan membuka direktori pada home/isnaini/modul2.


- ``while ((infolder = readdir(directory)) != NULL)`` untuk mengecek isi dalam folder sehingga dapat menjalankan perintah selanjutnya.


- ``name[panjang-4] == '.' && name[panjang-3] == 'p' && name[panjang-2] == 'n' && name[panjang-1] == 'g'``; perintah untuk menampung panjang karakter dari nama gambar tanpa ekstensi .png dan akan mereset serta membuat agar kondisi awal dari aray tidak berisi.


- ``strcat(Filename, name)``; berisi nama sumber yang akan dipindah.


- ``Filename[panjang-4] = '\0'`` ; perintah untuk menghapus dari belakang dengan urutan array


- ``strcat(Filename, "_grey.png")``; menambahkan karakter pada suatu ekstensi yang berbasis .png



**SOAL NO 2**
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

**Jawab:**

berikut ini adalah source code:
```
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

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
  while(1) {
    struct stat file;
    stat("/home/isnaini/hatiku/elen.ku",&file);
    if(!strcmp(getpwuid(file.st_uid)->pw_name,"www-data") && !strcmp(getgrgid(file.st_gid)->gr_name,"www-data")){
    chmod("/home/isnaini/hatiku/elen.ku", 0777);
    remove("/home/isnaini/hatiku/elen.ku");
    }
    sleep(3);
  }
  exit(EXIT_SUCCESS);
}
```


**Penjelasan :**

- ``struct stat file`` (adalah perintah untuk menyimpan data yang kompleks berupa file) 

- ``stat("/home/isnaini/hatiku/elen.ku",&file)``; (adalah suatu variable untuk menyimpan lokasi file yang disimpan)

-  ``if(!strcmp(getpwuid(file.st_uid)->pw_name,"www-data") && !strcmp(getgrgid(file.st_gid)->gr_name,"www-data")){``
 
(adalah suatu variable yang berfungsi untuk mencari owner dengan group yaitu dengan perintah strcmp yang nantinya akan membandingkan dua buah string).
 
-  ``chmod("/home/isnaini/hatiku/elen.ku", 0777)`` (adalah suatu perintah untuk mengubah permission file elen.ku, chmod berfungsi untuk mengatur sebuah hak akses atau sebuah permission terhadap file/ directory kepada user.)
 
 - ``remove("/home/isnaini/hatiku/elen.ku")``(adalah suatu perintah untuk menghapus file elen.ku)
 
 - ``sleep(3)``   (adalah sutau perintah delay selama 3 detik untuk menghapus file elen.ku)
 
 - ``exit(EXIT_SUCCESS)`` (adalah suatu perintah jika program berhasil, maka akan melakukan perintah Exit)
 
 
 
 
 
 **SOAL NO 3**
 
 
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 

Buatlah program C yang dapat :

i)  mengekstrak file zip tersebut
.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 

Catatan:

Gunakan fork dan exec.

Gunakan minimal 3 proses yang diakhiri dengan exec.

Gunakan pipe

Pastikan file daftar.txt dapat diakses dari text editor

**Penjelasan**
   
Berikut ini adalah source code:
```
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
```

**Penjelasan**
   
 -   ``pipe(pepiku);`` (adalah perintah untuk membuat pipe) 
        	
 -   ``pipe(pepiku+2);`` (adalah perintah untuk menambah pipe)
   
 -   ``execl("/usr/bin/unzip","unzip", "campur2.zip", NULL)`` (adalah perintah untuk mengekstrak file campur.zip)
   
 -   ``dup2(inipipe[1], STDOUT_FILENO);`` (adalah perintah untuk menyimpan hasil ls yang di write yang nantinya akan diduplicate yaitu dengan menggunakan perintah dup)
   
-   ``dup2(inipipe[0],STDIN_FILENO);``(adalah perintah untuk membaca hasil ls yang di read yang nantinya akan di duplicate yaitu dengan menggunakan perintah dup)
  
 -  ``close(pepiku[1]);`` (setiap perintah dup perlu close untuk dapat ditutup)
  
  -  `` int cetak = read(inipipe[2],hasil,sizeof(hasil));`` (adalah perintah untuk mengambil hasil grep)
   
  -  ``file = fopen("daftar.txt","w+");`` (adalah perintah yang akan membuka file daftar.txt)
   
   
 -   ``fprintf(file," Berikut Berupa File berformat .txt :\n%.*s\n",cetak,rest);`` (adalah perintah untuk memasukkan hasil ls grep ke dalam file)




 
 **SOAL NO 4**
 
 
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya.

Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang

baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah 

dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).

Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.
Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt
Catatan: 
dilarang menggunakan crontab
Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

**Jawab**
```
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

int main() 

{

pid_t pid, sid;

pid = fork();

if (pid < 0) 

{
    
exit(EXIT_FAILURE);
  
}

if (pid > 0) 

{
  
  exit(EXIT_SUCCESS);
  
 }

  umask(0);

  sid = setsid();

  if (sid < 0) 
  
  {
  
  exit(EXIT_FAILURE);
  
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  
  close(STDOUT_FILENO);
  
  close(STDERR_FILENO);
  
  int inc=1;

  while(1) 
  
  {
   
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

```


**Penjelasan:**

- ``int inc=1;`` (untuk melakukan inisialisasi untuk increment=1)

- ``char makanEnak[]="/home/galihpribadi04/Documents/makanan/makan_enak.txt";`` (adalah letak lokasi dimana file makan_enak.txt berada)

-  ``rentang = difftime(now, info.st_atime);`` (untuk Membuat file setiap 30 detik)
   
-  ``strcpy(path, "/home/galihpribadi04/Documents/makanan/makan_sehat");`` (untuk membuat file makan_sehat secara otomastis
  
strcpy adalah fungsi yang digunakan  untuk  menyalin  string  asal  ke-variabel  string  tujuan, dengan syarat string tujuan 

harus mempunyai tipe data dan dan ukuran  yang sama dengan string asal. File header yang harus disertakan adalah string.h.

Fungsi strcat digunakan untuk menggabungkan dua string menjadi satu).

- ``strcat(path,str);`` (perintah untuk menambahkan string sumber kebagian akhir dari string tujuan yang berupa path)

- ``sleep(5);`` (Fungsi sleep() mempunyai parameter dalam satuan detik dan mempunyai return value 0 atau sisa waktu yang tersisa bila di-interupsi oleh signal handler, sleep(5) akan menjalankan setiap 5 detik)




 **SOAL NO 5**
 
 
Kerjakan poin a dan b di bawah:

a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log

Ket:

Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]

Per menit memasukkan log#.log ke dalam folder tersebut

‘#’ : increment per menit. Mulai dari 1

b. Buatlah program c untuk menghentikan program di atas.

NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

**Jawab**

**nomor 5 a**
```
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

void crDaemon();

int main() {
  
  pid_t child;
  
  int status;
  
  int minute = 0;
  
  char dtime[20];
  
  char dir[100];
  
  char *uname;
  
  uname = getlogin();
  
  sprintf(dir, "/home/%s/log", uname);
  
  crDaemon();
  
  while(1) {
  
  if(minute%30 == 0){
      
      time_t now = time(NULL);
      
      struct tm *p = localtime(&now);
      
      strftime(dtime, sizeof(dtime)-1, "%Y:%m:%d-%H:%M", p);
    	
	}
    
      child = fork();
     
      if(child == 0){
     
       char cmd[200];
     
       sprintf(cmd, "%s/%s", dir, dtime);
     
       char *arg[4] = {"mkdir", "-p" ,cmd, NULL};
     
       execv("/bin/mkdir", arg);
    }
    
    while ((wait(&status)) > 0);
    
    kill(child, SIGKILL);
    
    minute+=1;
    
    child = fork();
    
    if(child == 0){
    
    char sr[] = "/var/log/syslog";
    
    char tg[200];
      
    sprintf(tg, "%s/%s/log%d.log", dir, dtime, minute);
    
    char *argv[4] = {"cp", sr, tg, NULL};
    
    execv("/bin/cp", argv);
    
    }
    
    while ((wait(&status)) > 0);
    
    kill(child, SIGKILL);
    
    sleep(60);
  
  }
  
  exit(EXIT_SUCCESS);
}

void crDaemon(){
    
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

}

```


**Penjelasan :**

Berfungsi untuk membuat file setiap 30 menit :
  ``` 
  while(1) {
    if(minute%30 == 0){
      time_t now = time(NULL);
      struct tm *p = localtime(&now);
      strftime(dtime, sizeof(dtime)-1, "%Y:%m:%d-%H:%M", p);
    }
   ```
    
Berfungsi untuk membuat parent
```
    child = fork();
    if(child == 0){
      char cmd[200];
      sprintf(cmd, "%s/%s", dir, dtime);
      char *arg[4] = {"mkdir", "-p" ,cmd, NULL};
      execv("/bin/mkdir", arg);// perintah untuk membuat folder
    }
    while ((wait(&status)) > 0);
    kill(child, SIGKILL);
```
   
Perintah untuk setiap 1 menit masukkan file log#.log
    ``minute+=1;
    
    
    
 
    
    
   




 
 


 
 























