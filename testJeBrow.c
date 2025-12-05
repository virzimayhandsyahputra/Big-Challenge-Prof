#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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
    if(targetStr == NULL && dest == NULL){return;}

    int i = 0, j = 0;
    while(targetStr[i] != '\0'){
        if(targetStr[i] == '.'){
            dest[j++] = ' ';
        }
        else if(ispunct(targetStr[i]) == 0){
            dest[j++] = tolower(targetStr[i]);
        }
        i++;
    }
    dest[j] = '\0';
}

int main(){
    char dest[2048];  
    FILE *fp = fopen("kecil.txt", "r");

    char line[4096];
    char noUrl[4096];
    
    // char *delims = " \n";

    while(fgets(line, sizeof(line), fp) != NULL){
        // char *token = strtok(line, delims);
        // while(token){
        //     printf("Token: %s\n", token);
        //     token = strtok(NULL, delims); 
        // }
        takeStringBetweenTag(line, noUrl);
        clearStrings(noUrl, noUrl);
        printf("%s", noUrl);
    }
    

    
    fclose(fp);
    
    return EXIT_SUCCESS;
}