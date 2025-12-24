#include <stdio.h>
#include "../include/view.h"
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
