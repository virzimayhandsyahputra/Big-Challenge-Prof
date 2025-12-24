#include <stdio.h>
#include "../include/parsing.h"

void takeStringBetweenTag(char *src, char *dest){
    if(src == NULL || dest == NULL){return;}
    dest[0] = '\0';
    int i = 0, j = 0;

    // remove url bro
    while(src[i] != '\0'){
        if(strncmp(&src[i], "<url>", 5) == 0){
            char *endText = strstr(&src[i], "</url>");
            if(endText == NULL) {i += 5; continue;}
            i = (endText - src) + 6;
            continue;
        }

        // ini untuk remove cssnya
        if(strncmp(&src[i], "< Font", 6) == 0){
            char *endCssTag = strstr(&src[i], "{pageSection1} ");
            if(endCssTag == NULL) {i += 6; continue;}
            i = (endCssTag - src) + 7;
            continue;
        }

        // finding tag
        if(src[i] == '<'){
            while(src[i] != '>' && src[i] != '\0'){ i++; }
            if(src[i] == '>') {
                i++;
                if(j > 0 && dest[j-1] != ' '){
                    dest[j++] = ' ';
                }
            }
            continue;
        }
        dest[j++] = src[i++];
    }
    dest[j] = '\0';
} 


void clearStrings(char *targetStr, char *dest){
    int i = 0, j = 0;
    bool lastSpace = false;
    while(targetStr[i] != '\0'){
        if(isalpha((char) targetStr[i])){
            dest[j++] = tolower(targetStr[i]);
            lastSpace = false;
        }
        else{
            if(lastSpace == false){
                dest[j++] = ' ';
                lastSpace = true;
            }
        } 
        i++;
    }
    if(j > 0 && dest[j-1] == ' '){j--;} 
    dest[j] = '\0';
}