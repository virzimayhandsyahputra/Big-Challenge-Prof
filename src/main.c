#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/globals.h"
#include "../include/parsing.h"
#include "../include/fileHandling.h"
#include "../include/structure.h"
#include "../include/view.h"

StoringWordsInfo listKataPerHuruf[ALPHABET_SIZE][MAX_WORD_PER_ALPHABETS];
int jumlahKataPerAbjad[ALPHABET_SIZE] = {0};

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

    handleMenu();

    return EXIT_SUCCESS;
}
