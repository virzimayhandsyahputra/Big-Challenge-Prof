#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/parsing.h"

void takeStringBetweenTag(char *src, char *dest){
    if(src == NULL || dest == NULL){return;}
    dest[0] = '\0';
    int i = 0, j = 0;
    bool textInTag = false;

    // remove url bro
    while(src[i] != '\0'){
        if(strncmp(&src[i], "<url>", 5) == 0){
            char *endText = strstr(&src[i], "</url>");
            if(endText == NULL) {i += 5; continue;}
            i = (endText - src) + 6;
            continue;
        }

        // ini untuk remove cssnyan
        if(strncmp(&src[i], "< Font", 6) == 0){
            char *endCssTag = strstr(&src[i], "{pageSection1} ");
            if(endCssTag == NULL) {i += 6; continue;}
            i = (endCssTag - src) + 7;
            continue;
        }

        // take string between body and title
        if(strncmp(&src[i], "<title>", 7) == 0) {   textInTag = true;   i += 7;     continue; }
        if(strncmp(&src[i], "</title>", 8) == 0){   textInTag = false;  i += 8;     continue; }
        if(strncmp(&src[i], "<body>", 6) == 0)  {   textInTag = true;   i += 6;     continue; }
        if(strncmp(&src[i], "</body>", 7) == 0) {   textInTag = false;  i += 7;     continue; }
        
        if(textInTag){  dest[j++] = src[i]; }
        i++;
    }
    dest[j] = '\0';
} 


void clearStrings(char *targetStr, char *dest){
    int i = 0, j = 0;
    bool lastSpace = false;
    while(targetStr[i] != '\0'){
        if(isalpha((unsigned char) targetStr[i])){
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