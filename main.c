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

StoringWordsInfo listKata[90000];
int countWord = 0;
char *delims = " \n";

int main(){
    FILE *fp = fopen("50k.txt", "r");
    if(fp == NULL){
        printf("[!] File Not Found");
        return EXIT_FAILURE;
    }

    char line[90000];
    char noTag[90000];
    
    while(fgets(line, sizeof(line), fp) != NULL){
        takeStringBetweenTag(line, noTag);
        clearStrings(noTag, noTag);
        char *token = strtok(noTag, delims);
        while(token != NULL){
            addWord(listKata, &countWord, token);
            token = strtok(NULL, delims); 
        }
        // printf("%s", noTag);
    }
    fclose(fp);

    writeToBin(listKata, &countWord, jumlahKataAbjad);

    return EXIT_SUCCESS;
}

void takeStringBetweenTag(char *targetStr, char *dest){
    if(targetStr == NULL && dest == NULL){return;}

    int i = 0, j = 0;

    // remove url bro
    while(targetStr[i] != '\0'){
        if(strncmp(&targetStr[i], "<url>", 5) == 0){
            char *endText = strstr(&targetStr[i], "</url>");
            if(endText == NULL) break;
            i = (endText - targetStr) + 6;
            continue;
        }

        // ini untuk remove cssnya
        if(strncmp(&targetStr[i], "< Font", 6) == 0){
            char *endCssTag = strstr(&targetStr[i], "{pageSection1} ");
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
    if(targetStr == NULL && dest == NULL){return;}

    int i = 0, j = 0;
    while(targetStr[i] != '\0'){
        if(targetStr[i] == ' '){ 
            dest[j++] = ' '; 
        } else if(targetStr[i] == '.' && isalpha((char) targetStr[i+1])){
            dest[j++] = ' ';
        } else if(isalpha((char) targetStr[i])){   
            dest[j++] = tolower(targetStr[i]);
        }
         
        i++;
    }
    dest[j] = '\0';
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
    jumlahKataAbjad[token[0] - 'a']++;
}

void writeToBin(StoringWordsInfo listKata[], int *countWord, int jumlahKataAbjad[]){
    FILE *binFptr = fopen("out.bin", "wb");
    if(binFptr == NULL){ return; }

    for(char abjad = 'a'; abjad <= 'z'; abjad++){
        int i = abjad - 'a';
        int jumlah = jumlahKataAbjad[i];

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