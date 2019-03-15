# SoalShift_modul2_C11
SoalShift modul2 Sistem Operasi kelas C

Isnaini Nurul KurniaSari 05111740000010

Argo Galih Pribadi       05111740000150


**SOAL NO 1


Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

**Jawab:


Dikarenakan terdapat aturan tidak boleh menggunakan crontab, maka kita menggunakan daemon hal ini dikarenakan perintah daemon agar file yang berekstensi .png dapat dipindahkan secara realtime atau periodik dan berjalan di belakang layar pada suatu folder ke /home/user/modul2/gambar. Daemon juga dapat membuat suatu aplikasi yang berjalan di sevice berjalan secara otomatis, daemon tidak memiliki parent proses ID.

Penjelasan :

``DIR *directory``; adalah suatu variable dengan nama folder yang menggunakan tipe data DIR.Jika digunakan tanpa parameter, perintah ini dapat menampilkan daftar berkas-berkas dan subdirektori yang terdapat di dalam direktori aktif. Berkas ini memiliki satu parameter, yakni lokasi direktori di mana hendak menampilkan daftar isi direktori. 


``struct dirent *infolder``; Struct adalah tipe data bentukan yang berisi kumpulan variabel-variabel yang berada dalam satu nama yang sama dan memiliki kaitan satu sama lain. Berbeda dengan array hanya berupa kumpulan variabel yang bertipe data sama, struct bisa memiliki variabel-variabel yang bertipe data sama atau berbeda, bahkan bisa menyimpan variabel yang bertipe data array atau struct itu sendiri. Variabel-variabel yang menjadi anggota struct disebut dengan elemen struct.


``chdir("/home/isnaini/modul2)``; akan mengubah direktori ke suatu path secara khusus 


``directory=opendir ("/home/isnaini/modul2/")``;adalah fungsi untuk membuka direktori handle gambar yaitu direktori asal dan akan menjalankan perintah pada gambar yang akan di pindah akan membuka direktori pada home/isnaini/modul2.


``while ((infolder = readdir(directory)) != NULL)`` untuk mengecek isi dalam folder sehingga dapat menjalankan perintah selanjutnya.


``name[panjang-4] == '.' && name[panjang-3] == 'p' && name[panjang-2] == 'n' && name[panjang-1] == 'g'``; perintah untuk menampung panjang karakter dari nama gambar tanpa ekstensi .png dan akan mereset serta membuat agar kondisi awal dari aray tidak berisi.


``strcat(Filename, name)``; berisi nama sumber yang akan dipindah.


``Filename[panjang-4] = '\0'`` ; perintah untuk menghapus dari belakang dengan urutan array


``strcat(Filename, "_grey.png")``; menambahkan karakter pada suatu ekstensi yang berbasis .png


