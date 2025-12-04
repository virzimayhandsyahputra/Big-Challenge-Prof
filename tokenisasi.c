#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    char kata[1024];
    int frekuensi;
    int panjangKata;
} WordInfo;

WordInfo words[2048];
int wordCount = 0;

int main(){
    char dest[2048];  
    FILE *fp = fopen("clean.txt", "r");

    char line[4096];
    char noUrl[4096];
    
    char *delims = " \n";

    while(fgets(line, sizeof(line), fp) != NULL){
        char *token = strtok(line, delims);
        while(token){
            printf("Token: %s\n", token);
            token = strtok(NULL, delims); 
        }
    }
    

    
    fclose(fp);
    
    return EXIT_SUCCESS;
}