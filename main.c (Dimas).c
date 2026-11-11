#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

#define MAX_PRODUK 50
#define PANJANG_NAMA 50
#define MAX_KERANJANG 50

char namaProduk[MAX_PRODUK][PANJANG_NAMA];
double harga[MAX_PRODUK];
int stok[MAX_PRODUK];
int jumlahTerjual[MAX_PRODUK];
int jumlahProduk = 0;

/* Membaca satu baris teks dan membuang karakter newline. */
void bacaTeks(const char *pesan, char *tujuan, size_t ukuran) {
    size_t panjang;
    printf("%s", pesan);
    if (fgets(tujuan, (int)ukuran, stdin) == NULL) {
        tujuan[0] = '\0';
        return;
    }
    panjang = strlen(tujuan);
    if (panjang > 0 && tujuan[panjang - 1] == '\n') {
        tujuan[panjang - 1] = '\0';
    } else {
        int karakter;
        while ((karakter = getchar()) != '\n' && karakter != EOF) { }
    }
}

/* Membaca bilangan bulat dengan validasi input. */
int bacaInt(const char *pesan) {
    char baris[100];
    char *akhir;
    long nilai;
    while (1) {
        bacaTeks(pesan, baris, sizeof(baris));
        errno = 0;
        nilai = strtol(baris, &akhir, 10);
        while (isspace((unsigned char)*akhir)) akhir++;
        if (baris[0] != '\0' && *akhir == '\0' && errno != ERANGE &&
            nilai >= -2147483647L - 1 && nilai <= 2147483647L) {
            return (int)nilai;
        }
        printf("Input harus berupa bilangan bulat. Silakan coba lagi.\n");
    }
}

/* Membaca bilangan desimal dengan validasi input. */
double bacaDouble(const char *pesan) {
    char baris[100];
    char *akhir;
    double nilai;
    while (1) {
        bacaTeks(pesan, baris, sizeof(baris));
        errno = 0;
        nilai = strtod(baris, &akhir);
        while (isspace((unsigned char)*akhir)) akhir++;
        if (baris[0] != '\0' && *akhir == '\0' && errno != ERANGE) {
            return nilai;
        }
        printf("Input harus berupa angka. Silakan coba lagi.\n");
    }
}

/* Mengubah teks menjadi huruf kecil untuk pencarian tanpa membedakan kapital. */
void keHurufKecil(const char *asal, char *hasil, size_t ukuran) {
    size_t i;
    for (i = 0; i + 1 < ukuran && asal[i] != '\0'; i++) {
        hasil[i] = (char)tolower((unsigned char)asal[i]);
    }
    hasil[i] = '\0';
}

int cariIndeksNama(const char *nama) {
    char target[PANJANG_NAMA];
    char pembanding[PANJANG_NAMA];
    int i;
    keHurufKecil(nama, target, sizeof(target));
    for (i = 0; i < jumlahProduk; i++) {
        keHurufKecil(namaProduk[i], pembanding, sizeof(pembanding));
        if (strcmp(target, pembanding) == 0) return i;
    }
    return -1;
}

void tampilkanDaftarProduk(void) {
    int i;
    if (jumlahProduk == 0) {
        printf("\nBelum ada produk.\n");
        return;
    }
    printf("\n================ DAFTAR PRODUK ================\n");
    printf("%-4s %-25s %-14s %-8s %-12s\n", "No.", "Nama Produk", "Harga (Rp)", "Stok", "Terjual");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < jumlahProduk; i++) {
        printf("%-4d %-25s %-14.2f %-8d %-12d\n", i + 1, namaProduk[i], harga[i], stok[i], jumlahTerjual[i]);
    }
}

void tambahProduk(void) {
    char nama[PANJANG_NAMA];
    double hargaBaru;
    int stokBaru;
    if (jumlahProduk >= MAX_PRODUK) {
        printf("Kapasitas produk sudah penuh (maksimal %d produk).\n", MAX_PRODUK);
        return;
    }
    bacaTeks("Masukkan nama produk: ", nama, sizeof(nama));
    if (nama[0] == '\0') {
        printf("Nama produk tidak boleh kosong.\n");
        return;
    }
    if (cariIndeksNama(nama) != -1) {
        printf("Produk dengan nama tersebut sudah ada.\n");
        return;
    }
    hargaBaru = bacaDouble("Masukkan harga produk (Rp): ");
    if (!isfinite(hargaBaru) || hargaBaru < 0) {
        printf("Harga tidak boleh negatif. Produk tidak ditambahkan.\n");
        return;
    }
    stokBaru = bacaInt("Masukkan stok awal: ");
    if (stokBaru < 0) {
        printf("Stok tidak boleh negatif. Produk tidak ditambahkan.\n");
        return;
    }
    strcpy(namaProduk[jumlahProduk], nama);
    harga[jumlahProduk] = hargaBaru;
    stok[jumlahProduk] = stokBaru;
    jumlahTerjual[jumlahProduk] = 0;
    jumlahProduk++;
    printf("Produk berhasil ditambahkan.\n");
}

void ubahProduk(void) {
    char nama[PANJANG_NAMA];
    int indeks, pilihan;
    double hargaBaru;
    int stokBaru;
    bacaTeks("Masukkan nama produk yang akan diubah: ", nama, sizeof(nama));
    indeks = cariIndeksNama(nama);
    if (indeks == -1) {
        printf("Produk tidak ditemukan.\n");
        return;
    }
    printf("Produk: %s | Harga: Rp%.2f | Stok: %d\n", namaProduk[indeks], harga[indeks], stok[indeks]);
    printf("1. Ubah harga\n2. Ubah stok\n3. Ubah harga dan stok\n");
    pilihan = bacaInt("Pilih perubahan: ");
    if (pilihan == 1 || pilihan == 3) {
        hargaBaru = bacaDouble("Masukkan harga baru (Rp): ");
        if (!isfinite(hargaBaru) || hargaBaru < 0) {
            printf("Harga tidak boleh negatif. Perubahan dibatalkan.\n");
            return;
        }
        harga[indeks] = hargaBaru;
    }
    if (pilihan == 2 || pilihan == 3) {
        stokBaru = bacaInt("Masukkan stok baru: ");
        if (stokBaru < 0) {
            printf("Stok tidak boleh negatif. Perubahan dibatalkan.\n");
            return;
        }
        stok[indeks] = stokBaru;
    }
    if (pilihan < 1 || pilihan > 3) {
        printf("Pilihan perubahan tidak tersedia.\n");
        return;
    }
    printf("Data produk berhasil diperbarui.\n");
}

void tambahStok(void) {
    char nama[PANJANG_NAMA];
    int indeks, tambahan;
    bacaTeks("Masukkan nama produk: ", nama, sizeof(nama));
    indeks = cariIndeksNama(nama);
    if (indeks == -1) {
        printf("Produk tidak ditemukan.\n");
        return;
    }
    tambahan = bacaInt("Masukkan jumlah stok yang ditambahkan: ");
    if (tambahan <= 0) {
        printf("Jumlah penambahan stok harus lebih dari nol.\n");
        return;
    }
    if (stok[indeks] > 2147483647 - tambahan) {
        printf("Penambahan ditolak karena jumlah stok terlalu besar.\n");
        return;
    }
    stok[indeks] += tambahan;
    printf("Stok %s berhasil ditambah. Stok sekarang: %d\n", namaProduk[indeks], stok[indeks]);
}

void cariProduk(void) {
    char kataKunci[PANJANG_NAMA];
    char namaKecil[PANJANG_NAMA], kataKecil[PANJANG_NAMA];
    int i, ditemukan = 0;
    bacaTeks("Masukkan nama produk yang dicari: ", kataKunci, sizeof(kataKunci));
    keHurufKecil(kataKunci, kataKecil, sizeof(kataKecil));
    printf("\nHasil pencarian:\n");
    for (i = 0; i < jumlahProduk; i++) {
        keHurufKecil(namaProduk[i], namaKecil, sizeof(namaKecil));
        if (strstr(namaKecil, kataKecil) != NULL) {
            printf("%d. %s | Harga: Rp%.2f | Stok: %d | Terjual: %d\n",
                   i + 1, namaProduk[i], harga[i], stok[i], jumlahTerjual[i]);
            ditemukan = 1;
        }
    }
    if (!ditemukan) printf("Produk tidak ditemukan.\n");
}

/*
 * Transaksi menggunakan keranjang sementara. Semua stok diperiksa dahulu.
 * Stok dan jumlah terjual baru diperbarui jika seluruh item valid.
 */
void transaksiPenjualan(void) {
    int indeksKeranjang[MAX_KERANJANG];
    int jumlahKeranjang[MAX_KERANJANG];
    int banyakItem = 0, nomor, kuantitas, i, j;
    double total = 0.0;
    char konfirmasi[10];

    if (jumlahProduk == 0) {
        printf("Belum ada produk untuk dijual.\n");
        return;
    }
    printf("\n========== TRANSAKSI PENJUALAN ==========\n");
    tampilkanDaftarProduk();
    printf("Masukkan nomor produk dan jumlah pembelian.\n");
    printf("Masukkan 0 pada nomor produk jika selesai memilih.\n");

    while (1) {
        nomor = bacaInt("Nomor produk (0 untuk selesai): ");
        if (nomor == 0) break;
        if (nomor < 1 || nomor > jumlahProduk) {
            printf("Nomor produk tidak ditemukan.\n");
            continue;
        }
        kuantitas = bacaInt("Jumlah pembelian: ");
        if (kuantitas <= 0) {
            printf("Jumlah pembelian harus lebih dari nol.\n");
            continue;
        }
        i = nomor - 1;
        for (j = 0; j < banyakItem; j++) {
            if (indeksKeranjang[j] == i) break;
        }
        if (j < banyakItem) {
            if (jumlahKeranjang[j] > 2147483647 - kuantitas) {
                printf("Jumlah pembelian terlalu besar.\n");
                continue;
            }
            jumlahKeranjang[j] += kuantitas;
        } else {
            if (banyakItem >= MAX_KERANJANG) {
                printf("Keranjang sudah mencapai batas item.\n");
                break;
            }
            indeksKeranjang[banyakItem] = i;
            jumlahKeranjang[banyakItem] = kuantitas;
            banyakItem++;
        }
        printf("Item dimasukkan ke keranjang.\n");
    }

    if (banyakItem == 0) {
        printf("Transaksi dibatalkan karena tidak ada produk yang dipilih.\n");
        return;
    }

    printf("\n=============== RINGKASAN ===============\n");
    for (j = 0; j < banyakItem; j++) {
        i = indeksKeranjang[j];
        printf("%-22s x %-5d = Rp%.2f\n", namaProduk[i], jumlahKeranjang[j], harga[i] * jumlahKeranjang[j]);
        total += harga[i] * jumlahKeranjang[j];
    }
    printf("Total pembayaran: Rp%.2f\n", total);

    for (j = 0; j < banyakItem; j++) {
        i = indeksKeranjang[j];
        if (jumlahKeranjang[j] > stok[i]) {
            printf("Transaksi ditolak: stok %s tidak mencukupi (tersedia %d, diminta %d).\n",
                   namaProduk[i], stok[i], jumlahKeranjang[j]);
            printf("Tidak ada stok atau jumlah terjual yang diubah.\n");
            return;
        }
        if (jumlahTerjual[i] > 2147483647 - jumlahKeranjang[j]) {
            printf("Transaksi ditolak: catatan jumlah terjual terlalu besar.\n");
            return;
        }
    }

    bacaTeks("Konfirmasi transaksi? (y/n): ", konfirmasi, sizeof(konfirmasi));
    if (tolower((unsigned char)konfirmasi[0]) != 'y' || konfirmasi[1] != '\0') {
        printf("Transaksi dibatalkan oleh pengguna.\n");
        return;
    }
    for (j = 0; j < banyakItem; j++) {
        i = indeksKeranjang[j];
        stok[i] -= jumlahKeranjang[j];
        jumlahTerjual[i] += jumlahKeranjang[j];
    }
    printf("Transaksi berhasil. Stok dan jumlah terjual telah diperbarui.\n");
}

void laporanPenjualan(void) {
    int i, totalUnit = 0, indeksTerlaris = -1;
    double totalPendapatan = 0.0;
    printf("\n=============== LAPORAN PENJUALAN ===============\n");
    printf("%-4s %-25s %-12s %-14s\n", "No.", "Nama Produk", "Terjual", "Pendapatan");
    printf("-------------------------------------------------------\n");
    for (i = 0; i < jumlahProduk; i++) {
        double pendapatanProduk = harga[i] * jumlahTerjual[i];
        printf("%-4d %-25s %-12d Rp%-13.2f\n", i + 1, namaProduk[i], jumlahTerjual[i], pendapatanProduk);
        totalUnit += jumlahTerjual[i];
        totalPendapatan += pendapatanProduk;
        if (indeksTerlaris == -1 || jumlahTerjual[i] > jumlahTerjual[indeksTerlaris]) {
            indeksTerlaris = i;
        }
    }
    printf("-------------------------------------------------------\n");
    printf("Total unit terjual : %d\n", totalUnit);
    printf("Total pendapatan   : Rp%.2f\n", totalPendapatan);
    if (indeksTerlaris == -1 || totalUnit == 0) {
        printf("Produk terlaris    : Belum ada penjualan.\n");
    } else {
        printf("Produk terlaris    : %s (%d unit)\n", namaProduk[indeksTerlaris], jumlahTerjual[indeksTerlaris]);
    }
    printf("Catatan: jika jumlah terjual tertinggi sama, produk pertama dalam daftar ditampilkan.\n");
}

/* Menukar seluruh atribut produk agar data tetap berada pada indeks yang sama. */
void tukarProduk(int a, int b) {
    char namaSementara[PANJANG_NAMA];
    double hargaSementara;
    int stokSementara, terjualSementara;
    strcpy(namaSementara, namaProduk[a]);
    strcpy(namaProduk[a], namaProduk[b]);
    strcpy(namaProduk[b], namaSementara);
    hargaSementara = harga[a]; harga[a] = harga[b]; harga[b] = hargaSementara;
    stokSementara = stok[a]; stok[a] = stok[b]; stok[b] = stokSementara;
    terjualSementara = jumlahTerjual[a]; jumlahTerjual[a] = jumlahTerjual[b]; jumlahTerjual[b] = terjualSementara;
}

void urutkanHarga(void) {
    int i, j, indeksMinimum;
    for (i = 0; i < jumlahProduk - 1; i++) {
        indeksMinimum = i;
        for (j = i + 1; j < jumlahProduk; j++) {
            if (harga[j] < harga[indeksMinimum]) indeksMinimum = j;
        }
        if (indeksMinimum != i) tukarProduk(i, indeksMinimum);
    }
    printf("Produk berhasil diurutkan berdasarkan harga termurah.\n");
    tampilkanDaftarProduk();
}

void urutkanTerjual(void) {
    int i, j, indeksMaksimum;
    for (i = 0; i < jumlahProduk - 1; i++) {
        indeksMaksimum = i;
        for (j = i + 1; j < jumlahProduk; j++) {
            if (jumlahTerjual[j] > jumlahTerjual[indeksMaksimum]) indeksMaksimum = j;
        }
        if (indeksMaksimum != i) tukarProduk(i, indeksMaksimum);
    }
    printf("Produk berhasil diurutkan berdasarkan jumlah terjual terbanyak.\n");
    tampilkanDaftarProduk();
}

void menuPengurutan(void) {
    int pilihan;
    printf("\n========== MENU PENGURUTAN ==========\n");
    printf("1. Harga termurah\n2. Jumlah terjual terbanyak\n0. Kembali\n");
    pilihan = bacaInt("Pilih menu: ");
    switch (pilihan) {
        case 1: urutkanHarga(); break;
        case 2: urutkanTerjual(); break;
        case 0: printf("Kembali ke menu utama.\n"); break;
        default: printf("Pilihan pengurutan tidak tersedia.\n");
    }
}

void cekStokMenipis(void) {
    int i, ditemukan = 0;
    printf("\n========== PRODUK DENGAN STOK KURANG DARI 5 ==========\n");
    for (i = 0; i < jumlahProduk; i++) {
        if (stok[i] < 5) {
            printf("- %s | Stok tersisa: %d\n", namaProduk[i], stok[i]);
            ditemukan = 1;
        }
    }
    if (!ditemukan) printf("Tidak ada produk dengan stok kurang dari 5.\n");
}

void isiDataAwal(void) {
    const char daftarNama[5][PANJANG_NAMA] = {
        "Nasi Goreng", "Mie Ayam", "Roti Cokelat", "Air Mineral", "Es Teh"
    };
    const double daftarHarga[5] = {15000, 12000, 7000, 4000, 5000};
    const int daftarStok[5] = {20, 15, 12, 30, 25};
    int i;
    jumlahProduk = 5;
    for (i = 0; i < 5; i++) {
        strcpy(namaProduk[i], daftarNama[i]);
        harga[i] = daftarHarga[i];
        stok[i] = daftarStok[i];
        jumlahTerjual[i] = 0;
    }
}

void tampilkanMenu(void) {
    printf("\n===============================================\n");
    printf("       SISTEM MONITORING KANTIN KAMPUS\n");
    printf("===============================================\n");
    printf("1. Lihat Daftar Produk\n");
    printf("2. Tambah Produk\n");
    printf("3. Ubah Produk\n");
    printf("4. Transaksi Penjualan\n");
    printf("5. Tambah Stok\n");
    printf("6. Cari Produk\n");
    printf("7. Urutkan Produk\n");
    printf("8. Laporan Penjualan\n");
    printf("9. Cek Stok Menipis\n");
    printf("0. Keluar\n");
    printf("===============================================\n");
}

int main(void) {
    int pilihan;
    isiDataAwal();
    printf("Selamat datang di Sistem Monitoring Stok dan Penjualan Kantin Kampus!\n");
    do {
        tampilkanMenu();
        pilihan = bacaInt("Masukkan pilihan menu: ");
        switch (pilihan) {
            case 1: tampilkanDaftarProduk(); break;
            case 2: tambahProduk(); break;
            case 3: ubahProduk(); break;
            case 4: transaksiPenjualan(); break;
            case 5: tambahStok(); break;
            case 6: cariProduk(); break;
            case 7: menuPengurutan(); break;
            case 8: laporanPenjualan(); break;
            case 9: cekStokMenipis(); break;
            case 0: printf("Terima kasih. Program selesai.\n"); break;
            default: printf("Pilihan menu tidak tersedia. Masukkan angka 0 sampai 9.\n");
        }
    } while (pilihan != 0);
    return 0;
}
