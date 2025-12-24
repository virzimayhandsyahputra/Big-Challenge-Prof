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

    processFile(fp);
    fclose(fp);
    handleMenu();

    return EXIT_SUCCESS;
}
