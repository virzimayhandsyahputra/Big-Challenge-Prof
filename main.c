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

int main(){
    char testStrings[128] = "<url>aduhai kerennyo, when yah jadi jaog</url>sedih la macam nie";

    char openTag[] = "<url>";
    char closeTag[] = "</url>";

    char *ambilPertama = strstr(testStrings, openTag);
    char *ambilKedua = strstr(ambilPertama, closeTag);

    ambilPertama += strlen(openTag);

    char dest[128];
    // printf("%d %d", strlen(openTag), strlen(closeTag));
    int length = strlen(ambilPertama) - strlen(ambilKedua);
    printf("%d\n\n", length);

    strncpy(dest, ambilPertama, length);
    printf("%s", dest);

    // printf("%s\n\n", ambilPertama);
    // printf("%s", ambilKedua);

    return EXIT_SUCCESS;
}