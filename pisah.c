#include <stdio.h>
#include <ctype.h>  

int main(){
    FILE *in = fopen ("sepuh.txt", "r");
    if(in == NULL){
        printf("File sepuh.txt tidak ada\n");
        return 1;
    }
    
    FILE *out = fopen ("ntah.txt", "w");
    if(out == NULL){
        printf("File ntah.txt tidak ada\n");
        fclose(in);
        return 1;
    }
    
    int removeDigit = 1;    
    int removePunct = 1;     
    int changeHuruf = 1;    
    
    char karakter;

    while((karakter = fgetc(in)) != EOF){
        if(removeDigit && isdigit((unsigned char)karakter)){
            continue;
        }
        if(removePunct && !isalpha((unsigned char)karakter) && karakter != ' ' && karakter != '\n'){
            continue;
        }
        if(changeHuruf){
            karakter = tolower((unsigned char)karakter);
        }
        fputc(karakter, out);
    }

    fclose(in);
    fclose(out);

    return 0;
}
