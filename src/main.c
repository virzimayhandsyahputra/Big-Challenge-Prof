#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/globals.h"
#include "../include/parsing.h"
#include "../include/fileHandling.h"
#include "../include/structure.h"
#include "../include/view.h"

StoringWordsInfo listKataPerHuruf[26][20000];
int jumlahKataPerAbjad[26] = {0};

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
    // for(int i = 0; i < sizeof(jumlahKataPerAbjad) / sizeof(jumlahKataPerAbjad[0]); i++){
    //     printf("%d ", jumlahKataPerAbjad[i]);
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
                if(jumlahKataPerAbjad[i] > 0){
                    perLetterInsertionSort(i);
                }
            }
            writeToBin();
            printf("Data berhasil disimpan ke out.bin\n");
        }else if(pilihan == 2){
            int jumlah;
            printf("Tampilkan berapa kata: ");
            scanf("%d", &jumlah);

            memset(jumlahKataPerAbjad, 0, sizeof(jumlahKataPerAbjad));

            readBin();
            showWords(jumlah);
        }
    }

    return EXIT_SUCCESS;
}
