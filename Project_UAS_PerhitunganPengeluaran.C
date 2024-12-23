#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum untuk kategori pengeluaran
enum kategori { MAKAN = 1, TRANSPORTASI, HIBURAN, LAINNYA };

// Union untuk menyimpan kategori dalam bentuk string
union KategoriUnion {
    enum kategori kategoriEnum;
    char kategoriStr[20];  // Menyimpan kategori sebagai string
};

// Struktur pengeluaran
struct pengeluaran {
    char deskripsi[100];
    union KategoriUnion kategori;  // Menggunakan union untuk kategori
    float jumlah;  // Jumlah pengeluaran dalam bentuk float
};

int main() {
    struct pengeluaran *data = NULL;  // Pointer untuk array pengeluaran
    int n = 0;  // Jumlah pengeluaran yang tercatat
    int max = 5;  // Alokasi awal untuk 5 pengeluaran
    char pilihan;
    float jumlah_uang, totalPengeluaran = 0;

    // Alokasi memori awal untuk 5 pengeluaran
    data = (struct pengeluaran*)malloc(max * sizeof(struct pengeluaran));

    if (data == NULL) {
        printf("Gagal mengalokasikan memori!\n");
        return 1;
    }

    // Input jumlah_uang
    printf("Masukkan jumlah uang anda: ");
    scanf("%f", &jumlah_uang);

    do {
        // Input deskripsi
        printf("\nPengeluaran ke-%d:\n", n + 1);
        printf("Masukkan deskripsi pengeluaran: ");
        getchar();  // Mengonsumsi newline
        fgets(data[n].deskripsi, sizeof(data[n].deskripsi), stdin);
        data[n].deskripsi[strcspn(data[n].deskripsi, "\n")] = 0; // Menghapus newline

        // Input kategori
        printf("Pilih kategori (1 = Makan, 2 = Transportasi, 3 = Hiburan, 4 = Lainnya): ");
        scanf("%d", &data[n].kategori.kategoriEnum);

        // Input jumlah pengeluaran
        printf("Masukkan jumlah pengeluaran: ");
        scanf("%f", &data[n].jumlah);

        // Menambahkan pengeluaran ke totalPengeluaran
        totalPengeluaran += data[n].jumlah;

        n++;

        // Jika jumlah pengeluaran mencapai batas, alokasikan ulang memori
        if (n == max) {
            max *= 2;  // Ganda ukuran alokasi memori
            data = realloc(data, max * sizeof(struct pengeluaran));

            if (data == NULL) {
                printf("Gagal mengalokasikan memori lebih banyak!\n");
                return 1;
            }
        }

        // Tanyakan apakah pengguna ingin menambah pengeluaran lagi
        printf("\nIngin menambah pengeluaran lagi? (y/n): ");
        getchar();  // Mengonsumsi newline
        scanf("%c", &pilihan);
    } while (pilihan == 'y' || pilihan == 'Y');

    // Menampilkan semua pengeluaran
    printf("\n--- Ringkasan Pengeluaran ---\n");
    for (int i = 0; i < n; i++) {
        printf("\nPengeluaran ke-%d:\n", i + 1);
        printf("Deskripsi: %s\n", data[i].deskripsi);
        printf("Kategori: %d\n", data[i].kategori.kategoriEnum);
        printf("Jumlah: %.f\n", data[i].jumlah);
    }

    // Menghitung pendapatan akhir
    float jumlah_uangSisa = jumlah_uang - totalPengeluaran;
    printf("\nTotal Pengeluaran: %.f\n", totalPengeluaran);
    printf("Jumlah uang sisa: %.f\n", jumlah_uangSisa);

    // Membebaskan memori setelah digunakan
    free(data);

    return 0;
}
