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
void readBin();
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


void addWord(char *token){
    if(token[0] < 'a' || token[0] > 'z'){ return; }
    
    int idHuruf = token[0] - 'a';
    int tokenLen = strlen(token);

    // cek dulu ada atau engga
    for(int i = 0; i < jumlahKataAbjad[idHuruf]; i++){
        if( listKataPerHuruf[idHuruf][i].panjangKata == tokenLen
            && strcmp(listKataPerHuruf[idHuruf][i].kata, token) == 0){
            listKataPerHuruf[idHuruf][i].frekuensi++;
            return;
        }
    }

    //kalo engga ada
    StoringWordsInfo *kataBaru = &listKataPerHuruf[idHuruf][jumlahKataAbjad[idHuruf]];
    kataBaru->abjad = token[0];
    kataBaru->panjangKata = tokenLen;
    strcpy(kataBaru->kata, token);
    kataBaru->frekuensi = 1;

    jumlahKataAbjad[idHuruf]++;
}

void perLetterInsertionSort(int idHuruf){
    int count = jumlahKataAbjad[idHuruf];
    StoringWordsInfo *arr = listKataPerHuruf[idHuruf];

    for(int i = 1; i < count; i++){
        StoringWordsInfo key = arr[i];
        int j = i - 1;

        while(j >= 0){
            bool swapElement = false;

            if(key.frekuensi != arr[j].frekuensi){
                if(key.frekuensi > arr[j].frekuensi){swapElement = true;}
            }
            else if(key.panjangKata != arr[j].panjangKata){
                if(key.panjangKata > arr[j].panjangKata){swapElement = true;}
            }
            else{
                if(strcmp(key.kata, arr[j].kata) > 0){swapElement = true;}
            }
                
            if(swapElement){
                arr[j+1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j+1] = key;
    }
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
