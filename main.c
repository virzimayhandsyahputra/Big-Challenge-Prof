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
// int countHowManyWord(StoringWordsInfo listKata[], int *countWord, char *abjad);

StoringWordsInfo listKata[90000];
int countWord = 0;
char *delims = " \n";

int main(){
    FILE *fp = fopen("5k.txt", "r");

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

    // int jumlahKataAbjad = 0;
    // for(int i = 'a'; i <= 'z'; i++){
    //     for(int j = 0; j <= countWord; j++){
    //         if(listKata[j].abjad == i){
    //             jumlahKataAbjad++;
    //         }
    //     }
    //     printf("%c Berjumlah %d\n", i, jumlahKataAbjad);
    //     jumlahKataAbjad = 0;
    // }

    
    // debug struct
    // printf("\n isi struct\n");
    // for(int i = 0; i < countWord; i++){
    //     printf("[%c][%d][%s][%d]\n", 
    //         listKata[i].abjad, 
    //         listKata[i].panjangKata, 
    //         listKata[i].kata,
    //         listKata[i].frekuensi
    //     );
    // }


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

// void writeToBin(char *fileName, StoringWordsInfo listKata[], int *countWord){
//     fwrite()
// }