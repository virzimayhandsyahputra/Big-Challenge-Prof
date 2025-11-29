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
    char kata[1024];
    int panjangKata;
    int frekuensi;
} InfoinKata;

typedef struct {
    char abjad;
    int jumlahKataAbjad;
    InfoinKata daftarKata[2048];
} GrupinAbjad;

//==pisahin tag==
void removeUrlTag(char *targetStr, char *dest){
    char openTag[] = "<url>";
    char closeTag[] = "</url>";

    char *ambilPertama = strstr(targetStr, openTag);
    char *ambilKedua = strstr(ambilPertama, closeTag);

    ambilKedua += strlen(closeTag);
    strcpy(dest, ambilKedua);
    printf("%s", dest);    
}

void takeStringBetweenTag(char *targetStr, char *dest){
    char *openTags = {"<title>", "<body>"};
    char *closeTags = {"</title>", "</body>"};

    char *ambilPertama = strstr(targetStr, openTag);
    char *ambilKedua = strstr(ambilPertama, closeTag);

    ambilPertama += strlen(openTag);
    int length = strlen(ambilPertama) - strlen(ambilKedua);

    strncpy(dest, ambilPertama, length);
} 

//==bersihin kata==
void cleanWord(const char *masukan, char *keluaran){
    int removeDigit = 1;
    int removePunct = 1;
    int changeHuruf = 1;

    int i = 0;
    int j = 0;
    char karakter;

    while((karakter = masukan[i]) != '\0'){
        if(removeDigit && isdigit((unsigned char)karakter)){
            i++;
            continue;
        }
        if(removePunct && !isalpha((unsigned char)karakter)){
            i++;
            continue;
        }
        if(changeHuruf){
            karakter = tolower((unsigned char)karakter);
        }
        keluaran[j] = karakter;
        j++;
        i++;
    }

    keluaran[j] = '\0';
}

//==urutin==

int main(){
    char testStrings[1024] = "<url>https_++soccer.sindonews.com+read+719945+56+inter-tawar-fabio-quagliarella-1361377464.html</url><title>Inter tawar Fabio Quagliarella</title><body>Sindonews.com Media di Italia, Mediaset melaporkan bahwa Inter Milan sudah mengajukan tawaran sebesar 7 juta poundsterling (setara Rp103 miliar) kepada Juventus. Nilai tawaran itu untuk memboyong Fabio Quagliarella pada bursa transfer musim panas mendatang. Di musim ini, pemain berusia 30 tahun ini gagal mendapatkan tempat utama di skuad Antonio Conte. Dia kalah bersaing dengan Sebastian Giovinco serta Mirko Vucinic. Kondisi itu yang coba dimanfaatkan oleh La Beneamata untuk membujuk mantan pemain Napoli tersebut agar mau berkostum biru hitam. Bahkan Mediaset mengabarkan bahwa pihak Inter sudah menghubungi agen Quagliarella, Beppe Bozzo untuk melakukan pembicaraan soal kemungkinan kliennya pindah ke Giuseppe Meazza. Transfer ini mungkin saja terjadi. Pasalnya, Inter memang sudah lama dihubung hubungkan dengan Quagliarella sejak musim panas tahun lalu.</body>";

    char openTag[] = "<url>";
    char closeTag[] = "</url>";

    char *ambilPertama = strstr(testStrings, openTag);
    char *ambilKedua = strstr(ambilPertama, closeTag);

    // ambilPertama += strlen(openTag);

    char dest[1024];
    // // printf("%d %d", strlen(openTag), strlen(closeTag));
    // int length = strlen(ambilPertama) - strlen(ambilKedua);
    // printf("%d\n\n", length);

    // strncpy(dest, ambilPertama, length);
    // printf("%s", dest);

    // printf("%s\n\n", ambilPertama);
    // printf("%s", ambilKedua);
    
    removeUrlTag(testStrings, dest);
    printf("%s", dest);    
    return EXIT_SUCCESS;
}
