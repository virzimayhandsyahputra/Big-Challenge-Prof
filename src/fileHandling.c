#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/fileHandling.h"
#include "../include/parsing.h"
#include "../include/structure.h"
#include "../include/globals.h"

void writeToBin(){
    FILE *binFptr = fopen(OUT_FILE_DIR, "wb");
    if(binFptr == NULL){ return; }

    for(int letterIdx = 0; letterIdx < 26; letterIdx++){
        char abjad = 'a' + letterIdx;
        int jumlah = jumlahKataUnikPerAbjad[letterIdx];

        fwrite(&abjad, sizeof(char), 1, binFptr);
        fwrite(&jumlah, sizeof(int), 1, binFptr);

        for(int j = 0; j < jumlah; j++){
            StoringWordsInfo *word = &listKataPerHuruf[letterIdx][j];
            fwrite(&word->panjangKata, sizeof(int), 1, binFptr);
            fwrite(word->kata, sizeof(char), word->panjangKata, binFptr);
            fwrite(&word->frekuensi, sizeof(int), 1, binFptr);
        }
    }
    fclose(binFptr);
}

void readBin(){
    FILE *binFptr = fopen(OUT_FILE_DIR, "rb");
    if(binFptr == NULL){
        printf("[!] File out.bin Not Found.\n");
        return;
    }

    for(int i = 0; i < 26; i++){
        char abjad;
        int jumlah;

        fread(&abjad, sizeof(char), 1, binFptr);
        fread(&jumlah, sizeof(int), 1, binFptr);
        
        int letterIdx = abjad - 'a';
        jumlahKataUnikPerAbjad[letterIdx] = jumlah;

        for(int j = 0; j < jumlah; j++){
            StoringWordsInfo *kataAbjadTersimpan = &listKataPerHuruf[letterIdx][j];
            fread(&kataAbjadTersimpan->panjangKata, sizeof(int), 1, binFptr);
            fread(kataAbjadTersimpan->kata, sizeof(char), kataAbjadTersimpan->panjangKata, binFptr);
            kataAbjadTersimpan->kata[kataAbjadTersimpan->panjangKata] = '\0';
            fread(&kataAbjadTersimpan->frekuensi, sizeof(int), 1, binFptr);
            kataAbjadTersimpan->abjad = abjad;
        }
    }
    fclose(binFptr);
}

void processFile(FILE *fp) {
    char line[MAX_LINE_LEN];
    char noTag[MAX_LINE_LEN];
    char strOnly[MAX_LINE_LEN];

    char delims[] = " \n";
    
    while(fgets(line, sizeof(line), fp) != NULL) {
        takeStringBetweenTag(line, noTag);
        clearStrings(noTag, strOnly);
        
        char *token = strtok(strOnly, delims);
        while(token != NULL) {
            addWord(token);
            token = strtok(NULL, delims);
        }
    }
}

bool checkBinFileExists(char *filename){
    FILE *fp = fopen(filename, "rb");
    if(fp != NULL){
        fclose(fp);
        return true;
    }
    return false;
}