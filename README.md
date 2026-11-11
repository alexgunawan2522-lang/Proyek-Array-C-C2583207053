# Sistem Monitoring Stok dan Penjualan Kantin Kampus

## Identitas Mahasiswa
- Nama Lengkap: **Dimas Adi Tiara Hayu**
- NIM: **C2583207053**
- Kelas: **PTI3A**
- Mata Kuliah: Algoritma dan Pemrograman Lanjutan
- Dosen Pengampu: Taofik Muhammad, M.Kom

## Deskripsi Proyek
Aplikasi console berbasis bahasa C untuk membantu pengelola kantin kampus mengelola data produk, stok, transaksi penjualan beberapa produk, pencarian, pengurutan, dan laporan penjualan. Data disimpan di dalam array selama program berjalan; program tidak menggunakan database atau file eksternal.

## Fitur
1. Menampilkan seluruh produk beserta harga, stok, dan jumlah terjual.
2. Menambahkan produk baru (maksimal 50 produk; tersedia 5 produk awal).
3. Mengubah harga dan/atau stok produk.
4. Melakukan satu transaksi yang berisi beberapa jenis produk.
5. Memeriksa kecukupan stok sebelum transaksi disimpan.
6. Menambah stok produk.
7. Mencari produk berdasarkan nama (tidak membedakan huruf besar/kecil; mendukung kata kunci).
8. Mengurutkan produk berdasarkan harga termurah.
9. Mengurutkan produk berdasarkan jumlah terjual terbanyak.
10. Menampilkan laporan jumlah terjual per produk, total unit, total pendapatan, dan produk terlaris.
11. Menampilkan produk dengan stok kurang dari 5.
12. Memvalidasi pilihan menu, produk, harga, stok, dan jumlah pembelian.

## Penerapan Array
Array menjadi struktur data utama sesuai ketentuan tugas:

| Nama array | Tipe | Fungsi |
|---|---|---|
| `namaProduk[50][50]` | Array karakter dua dimensi | Menyimpan nama maksimal 50 produk, setiap nama maksimal 49 karakter |
| `harga[50]` | Array `double` satu dimensi | Menyimpan harga setiap produk |
| `stok[50]` | Array `int` satu dimensi | Menyimpan stok setiap produk |
| `jumlahTerjual[50]` | Array `int` satu dimensi | Menyimpan akumulasi unit terjual setiap produk |

Variabel `jumlahProduk` menyimpan jumlah produk aktif. Indeks keempat array selalu merujuk pada produk yang sama. Ketika pengurutan dilakukan, seluruh atribut produk dipindahkan bersama agar data tidak tertukar.

## Data Awal
| Produk | Harga | Stok awal |
|---|---:|---:|
| Nasi Goreng | Rp15.000 | 20 |
| Mie Ayam | Rp12.000 | 15 |
| Roti Cokelat | Rp7.000 | 12 |
| Air Mineral | Rp4.000 | 30 |
| Es Teh | Rp5.000 | 25 |

## Persyaratan dan Kompilasi
Program menggunakan C standar (C11) dan dapat dikompilasi dengan GCC.

### Linux / macOS / terminal yang memiliki GCC
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o kantin
./kantin
```

### Windows (MinGW GCC)
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o kantin.exe
kantin.exe
```

Jika menggunakan Code::Blocks, buat proyek Console Application berbahasa C, ganti isi berkas utama dengan `main.c`, lalu Build and Run.

## Cara Menggunakan Program
1. Jalankan program.
2. Pilih menu dengan memasukkan angka 0–9.
3. Untuk transaksi, masukkan nomor produk dan jumlah pembelian. Masukkan `0` ketika semua produk sudah dipilih.
4. Periksa ringkasan transaksi, lalu masukkan `y` untuk mengonfirmasi atau `n` untuk membatalkan.
5. Gunakan menu laporan untuk melihat rekap penjualan.
6. Pilih `0` pada menu utama untuk keluar.

## Validasi dan Penanganan Kesalahan
- Pilihan menu di luar rentang yang tersedia ditolak dengan pesan.
- Nomor produk yang tidak tersedia dan nama produk yang tidak ditemukan ditangani.
- Nama produk kosong dan nama produk duplikat ditolak.
- Harga atau stok negatif ditolak.
- Penambahan stok harus lebih dari nol.
- Jumlah pembelian nol atau negatif ditolak.
- Transaksi yang melebihi stok ditolak tanpa mengubah stok maupun jumlah terjual.
- Penambahan produk ditolak ketika kapasitas 50 produk sudah penuh.
- Input angka yang bukan angka atau tidak sesuai tipe diminta ulang.

## Skenario Pengujian Wajib
Lakukan pengujian berikut setelah program dijalankan. Ambil screenshot terminal yang memperlihatkan input dan hasilnya. Simpan gambar di folder `screenshots/` dengan nama yang disarankan di bawah. Isi keterangan singkat di bawah setiap gambar berdasarkan hasil aktual yang terlihat di layar.

### 1. Tambah produk baru
- Pilih menu `2`.
- Nama: `MIE ALIM`, harga: `10000`, stok awal: `50`.
- Pilih menu `1` untuk memastikan produk muncul di daftar.
- Bukti:
  <img width="449" height="599" alt="1" src="https://github.com/user-attachments/assets/d6a3c2b6-05b4-4436-abbd-b5b190e9f4a8" />

![Bukti tambah produk]
<img width="512" height="599" alt="2" src="https://github.com/user-attachments/assets/d69362b8-ea04-4664-b435-0c6b22dc7887" />

Keterangan: [Saya sudah mengujinya beberapa kali dan terbukti itu tidak ada kekeliruan pada outputnya.]

### 2. Transaksi beberapa produk
- Pilih menu `4`.
- Pilih produk nomor `1`, jumlah `5`.
- Pilih produk nomor `5`, jumlah `6`.
- Pilih produk nomor `6`, jumlah `10`.
- Masukkan `0` untuk menyelesaikan pemilihan.
- Periksa subtotal setiap produk dan total pembayaran, lalu masukkan `y`.
- Bukti:
  <img width="512" height="599" alt="2" src="https://github.com/user-attachments/assets/0a59ef5a-2527-4d61-b1ca-0a4ad51ac5a9" />

Keterangan: [Saya sudah mengujinya beberapa kali dan terbukti itu tidak ada kekeliruan pada hasil deretan jumlah yang saya pesan.]

### 3. Pembaruan stok dan jumlah terjual
- Setelah transaksi berhasil, pilih menu `1`.
- Pastikan stok produk yang dibeli berkurang dan jumlah terjual bertambah.
- Bukti: `
  <img width="959" height="599" alt="19" src="https://github.com/user-attachments/assets/ab2e4936-c465-4084-9747-7e7bc5c7ed18" />

Keterangan: [sudah terbukti berkurang stoknya setelah melakukan transaksi.]

### 4. Stok tidak cukup
- Pilih menu `4`.
- Pilih produk yang stoknya diketahui, lalu masukkan jumlah pembelian yang lebih besar daripada stok tersedia.
- Selesaikan pemilihan dengan `0`.
- Pastikan transaksi ditolak dan data stok tidak berubah.
- Bukti:
  <img width="551" height="599" alt="4" src="https://github.com/user-attachments/assets/febc3de5-93b7-4b70-886f-1be3da0b8384" />

Keterangan: [Telah dicoba ketika memesan dengan melebihi dari stok, dan hasilnya ditolak.]

### 5. Laporan penjualan
- Pilih menu `8` setelah setidaknya satu transaksi berhasil.
- Periksa jumlah terjual per produk, total unit, total pendapatan, dan produk terlaris.
- Bukti:
  <img width="610" height="599" alt="5" src="https://github.com/user-attachments/assets/b386345f-3ef0-4d46-b86b-a0349e5daacc" />

### 6. Pengurutan
- Pilih menu `7`, kemudian `1` untuk mengurutkan harga dari termurah.
- Ulangi menu `7`, kemudian `2` untuk mengurutkan jumlah terjual dari terbanyak.
- Bukti:
  <img width="979" height="1198" alt="20" src="https://github.com/user-attachments/assets/3dec16de-56b0-47cb-b7f3-bc225348ba53" />
  <img width="494" height="599" alt="6" src="https://github.com/user-attachments/assets/46ea83bc-f722-4166-bec8-cb759c2f26ae" />

Keterangan: [Tuliskan apakah kedua urutan sudah sesuai.]

### 7. Pencarian dan pemeriksaan stok
- Pilih menu `6`, lalu cari nama atau bagian nama produk.
- Pilih menu `9` untuk menampilkan produk dengan stok kurang dari 5.
- Bukti:
  <img width="488" height="599" alt="21" src="https://github.com/user-attachments/assets/7c785d0f-b4d1-4627-8a19-00d49ea5d5be" />

Keterangan: [Sudah bisa muncul ketika memang stok yang tersedia kurang dari 5.]

## Catatan Pengujian Tambahan dengan contoh yang tidak valid atau salah (mencoba memberi angka diluar dari 0-9)

- Bukti : <img width="488" height="599" alt="21" src="https://github.com/user-attachments/assets/e9ea530b-097d-4ddf-8170-710e54673683" />

## Struktur Repository yang Disarankan
```text
Proyek-Array-C2583207053
├── main.c
├── README.md
└── screenshots/
    ├── 01-tambah-produk.png
    ├── 02-transaksi.png
    ├── 03-pembaruan-stok.png
    ├── 04-stok-tidak-cukup.png
    ├── 05-laporan.png
    ├── 06-pengurutan.png
    └── 07-pencarian-stok.png
└── Tambahan dengan memasukan contoh yang tidak valid
```
