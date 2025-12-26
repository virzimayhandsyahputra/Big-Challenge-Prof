#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/structure.h"
#include "../include/globals.h"

void addWord(char *token){
    if(token[0] < 'a' || token[0] > 'z'){ return; }
    
    int idHuruf = token[0] - 'a';
    int tokenLen = strlen(token);

    // cek dulu ada atau engga
    for(int i = 0; i < jumlahKataUnikPerAbjad[idHuruf]; i++){
        if( listKataPerHuruf[idHuruf][i].panjangKata == tokenLen
            && strcmp(listKataPerHuruf[idHuruf][i].kata, token) == 0){
            listKataPerHuruf[idHuruf][i].frekuensi++;
            return;
        }
    }

    //kalo engga ada
    StoringWordsInfo *kataBaru = &listKataPerHuruf[idHuruf][jumlahKataUnikPerAbjad[idHuruf]];
    kataBaru->abjad = token[0];
    kataBaru->panjangKata = tokenLen;
    strcpy(kataBaru->kata, token);
    kataBaru->frekuensi = 1;

    jumlahKataUnikPerAbjad[idHuruf]++;
}

void perLetterInsertionSort(int idHuruf){
    int count = jumlahKataUnikPerAbjad[idHuruf];
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
