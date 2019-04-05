# Laporan Soal Shift Modul 3
Laporan pengerjaan soal shift modul kedua  
Kelas Sistem Operasi E Jurusan Informatika Institut Teknologi Sepuluh Nopember  
Oleh Kelompok E10

---
## Nomor 1
### Soal
1.Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
	./faktorial 5 3 4
	3! = 6
	4! = 24
	5! = 120
### Jawab
membuat struct untuk menampung data
```c
typedef struct{
  int n;
  int hasil;
}number;
```

Gunakan perulangan untuk input data. Perulangan akan berjalan selama input tidak negatif
```c
while(1){
    scanf("%d", &x);
    y += 1;
    if(x < 0){
      break;
    }
    else if(x >=0){
      angka[y].n = x;
    }
  }
```

Urutkan input data agar terurut
```c
for(int i =0; i< y; i++){
    for(int j =i+1; j<y; j++){
      if(angka[i].n < angka [j].n){
        temp = angka[i].n;
        angka[i].n = angka[j].n;
        angka[j].n = temp;
      }
    }
  }
```

Buat thread sebanyak input dan joinkan semua thread
```c
for (int i =0; i<y; i++){
    pthread_create(&thread[i], NULL, faktorial, &angka[i]);
  }
  
for(int i=0; i<y; i++){
    pthread_join(thread[i], NULL);
  }
```

Hitung faktorial
```c
for (int i=1; i<=N->n; i++){
    fact *= i;
  }

  N->hasil = fact;
  printf("%d! = %d\n", N->n, fact);
```
## Nomor 2
### Soal
2.Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
a.Terdapat 2 server: server penjual dan server pembeli
b.1 server hanya bisa terkoneksi dengan 1 client
c.Server penjual dan server pembeli memiliki stok barang yang selalu sama
d.Client yang terkoneksi ke server penjual hanya bisa menambah stok
■Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
e.Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
■Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
f.Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
■Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
■Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
g.Server penjual akan mencetak stok saat ini setiap 5 detik sekali
h.Menggunakan thread, socket, shared memory
### Jawab
a. Server penjual
Pada thread pertama terdapat perulangan untuk menerima pesan dan ketika pesan bertuliskan "tambah", maka stok akan ditambah
```c
 while(1){
      valread = read( new_socket , buffer, 1024);
      if(strcmp(buffer,"tambah")==0){
        *stock += 1;
      }
   }
```
Pada thread kedua menjalankan perulangan untuk mencetak stok saat ini selama lima detik
```c
while(1){
      printf("Stock saat ini %d\n", *stock);
      sleep(5);
    }
  }
```

b. Server pembeli
Pada client pembeli menjalankan perulangan untuk menerima pesan dari client pembeli. Ketika pesan berupa "beli" maka stok akan dikurangi satu. Ketika stok lebih dari 0, maka cetak "transaksi berhasil", jika tidak cetak "transaksi gagal"
```c
while(1){
      valread = read( new_socket , buffer, 1024);
      if(strcmp(buffer,"beli")==0){
        if(*stock-1 < 0){
          send(new_socket , gagal, strlen(gagal) , 0 );
        }
else{
          *stock -= 1;
          send(new_socket , berhasil, strlen(berhasil) , 0 );
        }
      }
   }
```

c. Client penjual
Hanya mengirim pesan untuk menambah stok
```c
while(1){
    scanf("%s", msg);
    send(sock , msg, strlen(msg) , 0 );
  }
```

d. Client pembeli
Mengirim pesan "beli" dan menerima pesan balasan dari server pembeli
```c
while(1){
      valread = read( new_socket , buffer, 1024);
      if(strcmp(buffer,"beli")==0){
        if(*stock-1 < 0){
          send(new_socket , gagal, strlen(gagal) , 0 );
        }
else{
          *stock -= 1;
          send(new_socket , berhasil, strlen(berhasil) , 0 );
        }
      }
   }
```
## Nomor 3
### Soal
3.Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
a.Terdapat 2 karakter Agmal dan Iraj
b.Kedua karakter memiliki status yang unik
■Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
■Iraj memiliki Spirit_Status, di awal program memiliki status 100
■Terdapat 3 Fitur utama
●All Status, yaitu menampilkan status kedua sahabat
Ex: Agmal WakeUp_Status = 75 
      Iraj Spirit_Status = 30
●“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
●“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
■Terdapat Kasus yang unik dimana:
●Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
●Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
■Program akan berhenti jika Salah Satu :
●WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
●Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)


■Syarat Menggunakan Lebih dari 1 Thread

###Jawab
Deklarasi status awal dan pilihan menu
```c
status.agmal = 0;
  status.iraj = 100;
  printf("Fitur-fitur :\n");
  printf("Tekan 1 untuk mengaktifkan fitur 'Agmal Ayo Bangun'\n");
  printf("Tekan 2 untuk mengaktifkan fitur 'Iraj Ayo Tidur\n'");
  printf("Tekan 3 untuk mengaktifkan fitur 'Menampilkan All status'\n");
```
Input menu yang akan dipilih dan jalankan thread. Untuk menu 3 makan cetak status masing-masing
```c
 scanf("%d", &input);

      if(input == 1){
          z =0;
          pthread_create(&thread1, NULL, fungsi, &status);
      }
      else if(input ==2){
          z=1;
          pthread_create(&thread2, NULL, fungsi, &status);
      }
    
      else if(input == 3){
        printf("Agmal WakeUp_status %d\nIraj Spirit_status %d\n", status.agmal, status.iraj);
      }
 ```   
 
 fungsi yang dijalankan thread 2 untuk mengrangi status iraj
 ```c
 if(berhentiI == 1){
      sleep(10);
      berhentiI=0;
    }
    else{
      stat->iraj -= 20;
      flagI++;

      if(flagI == 3){
        berhentiA =1;
        printf("Agmal Ayo Bangun disabled 10 s\n");
        flagI = 0;
      }
 ```
 
 Fungsi thread 1 untuk menambah status agmal
 ```c
 if(berhentiA == 1){
      sleep(10);
      berhentiI=0;
    }
    else{
      stat->agmal += 15;
      flagA++;
      if(flagA == 3){
        berhentiI =1;
        printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
        flagA = 0;
```

## Nomor 4
### Soal
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
* Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
* Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
* Ketika Mengekstrak file .zip juga harus secara bersama-sama
* Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
* Wajib Menggunakan Multithreading
* Boleh menggunakan system

### Jawab
Solusinya adalah dengan melakukan multi threading lalu menggunakan system() untuk mengesekusi ps-aux lalu di pipe ke tail untuk mendapatkan 10 proses saja lalu dimasukkan ke dalam file, hasilnya lalu di zip dan dilakukan sleep selama 15 detik lalu di unzip kembali.   
Karena 2 masalah serupa mesti dilakukan secara bersaaman, hal ini dilakukan dengan menggunakan multithreading

## Nomor 5

### Soal

Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta.  
1. Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.  
2. Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
3. Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).  
4. Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.  
5. Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian.   
6. Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.  
Pembeli (terintegrasi dengan game)
Dapat mengecek stok makanan yang ada di toko.
Jika stok ada, pembeli dapat membeli makanan.
Penjual (terpisah)
Bisa mengecek stok makanan yang ada di toko
Penjual dapat menambah stok makanan.
	Spesifikasi program:

* Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
* Program terdiri dari 3 scene yaitu standby, battle, dan shop.
Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

      Standby Mode
      Health : [health status]
      Hunger : [hunger status]
      Hygiene : [hygiene status]
      Food left : [your food stock]
      Bath will be ready in [cooldown]s
      Choices
      Eat
      Bath
      Battle
      Shop
      Exit

Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

      Battle Mode
      Monster’s Health : [health status]
      Enemy’s Health : [enemy health status]
      Choices
      Attack
      Run

Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

		Shop Mode
		Shop food stock : [shop food stock]
		Your food stock : [your food stock]
		Choices
            Buy
            Back

Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

    Shop
    Food stock : [shop food stock]
    Choices
    Restock
    Exit

Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

### Jawab

dibuat 6 thread yang masing masing mengatur:
* refresh scene
* counter hygiene
* counter hunger
* counter health
* coutner bath cooldown
* scene organizer
  
refresh scene berguna untuk me-refresh output setiap detik  
counter hygiene,hunger,health dan cooldown berguna untuk menghitung perubahan ke 4 nilai tersebut independen dari thread yang lain  
Scene organizer berguna untuk mengatur masuknya input ke setiap scene  

lalu dibuat program shop yang serupa dengan program ini, hanya saja memiliki satu scene dan tidak harus melakukan counter yang banyak, sehingga satu thread sudah cukup untuk program tersebut.

