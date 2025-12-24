#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/view.h"
#include "../include/fileHandling.h"
#include "../include/structure.h"
#include "../include/globals.h"

void showWords(int jumlah){
    for(int letterIdx = 0; letterIdx < 26; letterIdx++){
        char abjad = 'a' + letterIdx;
        printf("%c {", abjad);
        
        int tampil = 0;
        int count = jumlahKataPerAbjad[letterIdx];

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

void printMenu(){
    printf("\nMenu:\n");
    printf("1. Simpan ke file binari\n");
    printf("2. Tampilkan n kata per abjad\n");
    printf("3. Keluar\n");
    printf("Pilihan Anda: ");
}

void handleMenuOption1(){
    for(int i = 0; i < 26; i++){
                if(jumlahKataPerAbjad[i] > 0){
                    perLetterInsertionSort(i);
                }
    }
    writeToBin();
    printf("Data berhasil disimpan ke out.bin\n");
}

void handleMenuOption2(){
    if(checkBinFileExists("./bin/out.bin") != true){
        printf("[!] File out.bin belum ada, harap pilih opsi 1 terlebih dahulu\n");
        return;
    }

    int jumlah;
    printf("Tampilkan berapa kata (0<n<=25): ");
    scanf("%d", &jumlah);
    
    if(jumlah < 0 || jumlah > 25) {
        printf("Jumlah tidak valid! Harus antara 1-25\n");
        return;
    }
    
    memset(jumlahKataPerAbjad, 0, sizeof(jumlahKataPerAbjad));
    readBin();
    showWords(jumlah);
}

void handleMenu(){
    int pilihan;

    do {
        printMenu();
        if(scanf("%d", &pilihan) != 1){
            printf("[!] Input tidak valid");
            return;
        };

        switch(pilihan){
            case 1:
                handleMenuOption1();
                break;
            case 2:
                handleMenuOption2();
                break;
            case 3:
                printf("[+] Program Selesai.\n");
                break;
            default:
                printf("[!] Pilihan Tidak Valid, Harap Pilih 1-3\n");
        }
    } while(pilihan != 3);
}
