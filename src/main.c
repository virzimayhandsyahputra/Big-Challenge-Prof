#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD 90000

typedef struct {
    char abjad; 
    int panjangKata;
    char kata[1024];
    int frekuensi;
} StoringWordsInfo;

StoringWordsInfo listKataPerHuruf[26][20000];
int jumlahKataAbjad[26] = {0};

void addWord(char *token);
void perLetterInsertionSort(int hurufId);
void showWords(int jumlah);

int main(){
    char namaFile[256];

    printf("Masukkan nama file input: ");
    scanf("%255s", namaFile);

    FILE *fp = fopen(namaFile, "r");
    if(fp == NULL){
        printf("[!] File Not Found\n");
        return EXIT_FAILURE;
    }

    char line[4096];
    char noTag[4096];
    char strOnly[4096];

    while(fgets(line, sizeof(line), fp) != NULL){
        takeStringBetweenTag(line, noTag);
        clearStrings(noTag, strOnly);
        // printf("%s", strOnly);

        char *token = strtok(strOnly, " ");
        while(token != NULL){
            addWord(token);
            // printf("%s", token)
            token = strtok(NULL, " \n");
        }
    }
    fclose(fp);

    // untuk debug brow (biarin aja)
    // for(int i = 0; i < sizeof(jumlahKataAbjad) / sizeof(jumlahKataAbjad[0]); i++){
    //     printf("%d ", jumlahKataAbjad[i]);
    // }

    int pilihan = 0;

    while(pilihan != 3){
        printf("\nMenu:\n");
        printf("1. Simpan ke file binari\n");
        printf("2. Tampilkan n kata per abjad\n");
        printf("3. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
            
        if(pilihan == 1){
            for(int i = 0; i < 26; i++){
                if(jumlahKataAbjad[i] > 0){
                    perLetterInsertionSort(i);
                }
            }
            writeToBin();
            printf("Data berhasil disimpan ke out.bin\n");
        }else if(pilihan == 2){
            int jumlah;
            printf("Tampilkan berapa kata: ");
            scanf("%d", &jumlah);

            memset(jumlahKataAbjad, 0, sizeof(jumlahKataAbjad));

            readBin();
            showWords(jumlah);
        }
    }

    return EXIT_SUCCESS;
}





void showWords(int jumlah){
    for(int letterIdx = 0; letterIdx < 26; letterIdx++){
        char abjad = 'a' + letterIdx;
        printf("%c {", abjad);
        
        int tampil = 0;
        int count = jumlahKataAbjad[letterIdx];

        for(int i = 0; i < count && tampil < jumlah; i++){
            StoringWordsInfo *word = &listKataPerHuruf[letterIdx][i];
            printf("%s (%d)", word->kata, word->frekuensi);
            tampil++;
            if(tampil < jumlah && i + 1 < count){
                printf(", ");
            }
        }
        printf("}\n");
    }
}
