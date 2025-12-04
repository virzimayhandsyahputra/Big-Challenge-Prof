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

// typedef struct {
//     char kata[1024];
//     int frekuensi;
//     int panjangKata;
// }

void takeStringBetweenTag(char *targetStr, char *dest){
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
            while(targetStr[i] != '>' && targetStr[i] != '\0'){
                i++;
            }
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


int main(){
    char dest[4096];
    printf("%s", dest);  
    
    FILE *fp = fopen("kecil.txt", "r");

    char line[4096];
    char noTag[4096];
    
    while(fgets(line, sizeof(line), fp) != NULL){
        takeStringBetweenTag(line, noTag);
        clearStrings(noTag, noTag);
        // char *token = strtok(noTag, delims);
        // while(token != NULL){
        //     token = strtok(NULL, delims); 
        // }
        printf("%s", noTag);
    }

    fclose(fp);
    
    return EXIT_SUCCESS;
}