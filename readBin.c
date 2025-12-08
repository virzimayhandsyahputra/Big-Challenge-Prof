#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char abjad; 
    int panjangKata;
    char kata[1024];
    int frekuensi;
} StoringWordsInfo;

StoringWordsInfo listKata[90000];

void writeToBin(StoringWordsInfo listKata[], int *countWord, int jumlahKataAbjad[]){
    FILE *binFptr = fopen("out.bin", "wb");
    if(binFptr == NULL){ return; }

    for(char abjad = 'a'; abjad <= 'z'; abjad++){
        int i = abjad - 'a';
        int jumlah = jumlahKataAbjad[i];

        fwrite(&abjad, sizeof(char), 1, binFptr);
        fwrite(&jumlah, sizeof(int), 1, binFptr);

        for(int j = 0; j < *countWord; j++){
            if(listKata[j].abjad == abjad){
                fwrite(&listKata[j].panjangKata, sizeof(int), 1, binFptr);
                fwrite(&listKata[j].kata, sizeof(char), listKata[j].panjangKata, binFptr);
                fwrite(&listKata[j].frekuensi, sizeof(int), 1, binFptr);
            }
        }
    }
    fclose(binFptr);
}

int main(){
    FILE *fp = fopen("out.bin", "rb");
    if(fp == NULL){
        printf("Gagal membuka file bin\n");
        return 1;
    }

    // File output txt
    FILE *out = fopen("output.txt", "w");
    if(out == NULL){
        printf("Gagal membuat file output.txt\n");
        fclose(fp);
        return 1;
    }

    char abjad;
    int jumlah;

    for(int i = 0; i < 26; i++){
        // baca huruf
        fread(&abjad, sizeof(char), 1, fp);

        // baca jumlah kata
        fread(&jumlah, sizeof(int), 1, fp);

        fprintf(out, "\nHuruf: %c | Jumlah kata: %d\n", abjad, jumlah);

        for(int j = 0; j < jumlah; j++){
            int panjangKata;
            fread(&panjangKata, sizeof(int), 1, fp);

            char kata[1024];
            fread(kata, sizeof(char), panjangKata, fp);
            kata[panjangKata] = '\0';   

            int frekuensi;
            fread(&frekuensi, sizeof(int), 1, fp);

            fprintf(out, "  - %s (%d kali)\n", kata, frekuensi);
        }
    }

    fclose(fp);
    fclose(out);

    printf("Output berhasil disimpan ke file output.txt\n");
    return 0;
}
