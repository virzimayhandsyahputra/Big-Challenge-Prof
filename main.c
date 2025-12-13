#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// typedef Struct {
//     char abjad;
//     int jumlahKataAbjad;
//     int panjangKata;
//     char kata[1024];
//     int frekuensi;
// } InilahNantiYangBakalDitampilinKeOutputnyaKING
#define MAX_WORD 90000

typedef struct {
    char abjad; 
    int panjangKata;
    char kata[1024];
    int frekuensi;
} StoringWordsInfo;

int jumlahKataAbjad[26] = {0};

void takeStringBetweenTag(char *targetStr, char *dest);
void clearStrings(char *targetStr, char *dest);
void addWord(StoringWordsInfo listKata[], int *countWord, char *token);
void writeToBin(StoringWordsInfo listKata[], int *countWord, int jumlahKataAbjad[]);
void insertionSort(StoringWordsInfo listKata[], int *countWord);
void readBin(StoringWordsInfo listKata[], int *countWord, int jumlahKataAbjad[]);
void showWords(StoringWordsInfo listKata[], int countWord, int jumlah);

StoringWordsInfo listKata[MAX_WORD];
int countWord = 0;
char *delims = " \n";

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

    while(fgets(line, sizeof(line), fp) != NULL){
        takeStringBetweenTag(line, noTag);
        clearStrings(noTag, noTag);

        char *token = strtok(noTag, delims);
        while(token != NULL){
            addWord(listKata, &countWord, token);
            token = strtok(NULL, delims);
        }
    }
    fclose(fp);

    int pilihan = 0;

    while(pilihan != 3){
        printf("\nMenu:\n");
        printf("1. Simpan ke file binari\n");
        printf("2. Tampilkan n kata per abjad\n");
        printf("3. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        if(pilihan == 1){
            writeToBin(listKata, &countWord, jumlahKataAbjad);
            printf("Data berhasil disimpan ke out.bin\n");
        }else if(pilihan == 2){
            int jumlah;
            printf("Tampilkan berapa kata: ");
            scanf("%d", &jumlah);

            countWord = 0;
            memset(jumlahKataAbjad, 0, sizeof(jumlahKataAbjad));

            readBin(listKata, &countWord, jumlahKataAbjad);
            showWords(listKata, countWord, jumlah);
        }
    }

    return EXIT_SUCCESS;
}

void takeStringBetweenTag(char *targetStr, char *dest){
    if(targetStr == NULL || dest == NULL){return;}

    int i = 0, j = 0;

    // remove url bro
    while(targetStr[i] != '\0'){
        if(strncmp(&targetStr[i], "<url>", 5) == 0){
            char *endText = strstr(&targetStr[i], "</url>");
            if(endText == NULL) {i += 5; continue;}
            i = (endText - targetStr) + 6;
            continue;
        }

        // ini untuk remove cssnya
        if(strncmp(&targetStr[i], "< Font", 6) == 0){
            char *endCssTag = strstr(&targetStr[i], "{pageSection1} ");
            if(endCssTag == NULL) {i += 6; continue;}
            i = (endCssTag - targetStr) + 7;
            continue;
        }

        // finding tag
        if(targetStr[i] == '<'){
            while(targetStr[i] != '>' && targetStr[i] != '\0'){ i++; }
            if(targetStr[i] == '>') {
                i++;
                if(j > 0 && dest[j-1] != ' '){
                    dest[j++] = ' ';
                }
            }
            continue;
        }
        dest[j++] = targetStr[i++];
    }
    dest[j] = '\0';
} 

void clearStrings(char *targetStr, char *dest){
    if(targetStr == NULL || dest == NULL){return;}

    int i = 0, j = 0;
    bool lastSpace = false;
    while(targetStr[i] != '\0'){
        if(isalpha((unsigned char) targetStr[i])){
            dest[j++] = tolower((unsigned char) targetStr[i]);
            lastSpace = false;
        }
        else if(i > 0 && targetStr[i+1] != '\0' && targetStr[i] == '.' && isalpha(targetStr[i-1]) && isalpha(targetStr[i+1])){
            dest[j++] = ' ';
        }
        else if(targetStr[i] == ' '){
            if(!lastSpace){
                dest[j++] = ' ';
                lastSpace = true;
            }
        } 
        i++;
    }
    if(j > 0 && dest[j-1] == ' '){dest[j-1] = '\0';} 
    else {dest[j] = '\0';}
}

void addWord(StoringWordsInfo listKata[], int *countWord, char *token){
    // cek dulu ada atau engga
    for(int i = 0; i < *countWord; i++){
        if(strcmp(listKata[i].kata, token) == 0){
            listKata[i].frekuensi++;
            return;
        }
    }

    //kalo engga ada
    listKata[*countWord].abjad = token[0]; 
    strcpy(listKata[*countWord].kata, token);
    listKata[*countWord].frekuensi = 1;
    listKata[*countWord].panjangKata = strlen(token);

    
    (*countWord)++;
    if(token[0] >= 'a' && token[0] <= 'z'){
        jumlahKataAbjad[token[0] - 'a']++;
    }
}

void insertionSort(StoringWordsInfo listKata[], int *countWord){
    for(int i = 1; i < *countWord; i++){
        StoringWordsInfo key = listKata[i];
        int j = i - 1;

        while(j >= 0){
            bool swap = false;
            if(key.abjad != listKata[j].abjad){
                if(key.abjad < listKata[j].abjad){swap=true;}
            } 
            else if(key.frekuensi != listKata[j].frekuensi){
                if(key.frekuensi > listKata[j].frekuensi){swap=true;}
            }
            else if(key.panjangKata != listKata[j].panjangKata){
                if(key.panjangKata > listKata[j].panjangKata){swap=true;}
            }
            else{
                if(strcmp(key.kata, listKata[j].kata) > 0){swap=true;}
            }
                
            if(swap == true){
                listKata[j+1] = listKata[j];
                j--;
            } else {break;}
        }
        listKata[j+1] = key;
    }
}

void writeToBin(StoringWordsInfo listKata[], int *countWord, int jumlahKataAbjad[]){
    FILE *binFptr = fopen("out.bin", "wb");
    if(binFptr == NULL){ return; }

    for(char abjad = 'a'; abjad <= 'z'; abjad++){
        int jumlah = jumlahKataAbjad[abjad - 'a'];

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

void readBin(StoringWordsInfo listKata[], int *countWord, int jumlahKataAbjad[]){
    FILE *binFptr = fopen("out.bin", "rb");
    if(binFptr == NULL){
        printf("[!] File out.bin Not Found.\n");
        return;
    }

    for(int i = 0; i < 26; i++){
        char abjad;
        int jumlah;

        fread(&abjad, sizeof(char), 1, binFptr);
        fread(&jumlah, sizeof(int), 1, binFptr);
        jumlahKataAbjad[i] = jumlah;

        for(int j = 0; j < jumlah; j++){
            fread(&listKata[*countWord].panjangKata, sizeof(int), 1, binFptr);
            fread(listKata[*countWord].kata, sizeof(char), listKata[*countWord].panjangKata, binFptr);
            listKata[*countWord].kata[listKata[*countWord].panjangKata] = '\0';
            fread(&listKata[*countWord].frekuensi, sizeof(int), 1, binFptr);
            listKata[*countWord].abjad = abjad;
            (*countWord)++;
        }
    }
    fclose(binFptr);
}

void showWords(StoringWordsInfo listKata[], int countWord, int jumlah){
    for(char abjad = 'a'; abjad <= 'z'; abjad++){
        printf("%c {", abjad);
        int tampil = 0;

        for(int i = 0; i < countWord && tampil < jumlah; i++){
            if(listKata[i].abjad == abjad){
                printf("%s (%d)", listKata[i].kata, listKata[i].frekuensi);
                tampil++;
                if(tampil < jumlah){
                    printf(", ");
                }
            }
        }
        printf("}\n");
    }
}
