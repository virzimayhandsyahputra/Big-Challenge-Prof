#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char abjad;
    int panjangKata;
    char kata[1024];
    int frekuensi;
} StoringWordsInfo;

int main() {
    FILE *fp = fopen("out.bin", "rb");
    if (!fp) {
        printf("Gagal membuka out.bin\n");
        return 1;
    }

    char abjad;
    int jumlah;
    
    while (fread(&abjad, sizeof(char), 1, fp) == 1) {
        fread(&jumlah, sizeof(int), 1, fp);

        printf("\n=== Abjad: %c | Jumlah kata: %d ===\n", abjad, jumlah);

        for (int i = 0; i < jumlah; i++) {

            StoringWordsInfo data;

            data.abjad = abjad;

            fread(&data.panjangKata, sizeof(int), 1, fp);
            fread(data.kata, sizeof(char), data.panjangKata, fp);
            data.kata[data.panjangKata] = '\0';   // null terminator

            fread(&data.frekuensi, sizeof(int), 1, fp);

            printf("Kata: %-20s | Panjang: %d | Frekuensi: %d\n",
                   data.kata, data.panjangKata, data.frekuensi);
        }
    }

    fclose(fp);
    return 0;
}
