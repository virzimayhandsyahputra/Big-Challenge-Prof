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
            };
            continue;
        }
        dest[j++] = targetStr[i++];
    }
    dest[j] = '\0';
} 


int main(){
    // char testStrings[2048] = "<url>https_++soccer.sindonews.com+read+719945+56+inter-tawar-fabio-quagliarella-1361377464.html</url><title>Inter tawar Fabio Quagliarella</title><body>Sindonews.com Media di Italia, Mediaset melaporkan bahwa Inter Milan sudah mengajukan tawaran sebesar 7 juta poundsterling (setara Rp103 miliar) kepada Juventus. Nilai tawaran itu untuk memboyong Fabio Quagliarella pada bursa transfer musim panas mendatang. Di musim ini, pemain berusia 30 tahun ini gagal mendapatkan tempat utama di skuad Antonio Conte. Dia kalah bersaing dengan Sebastian Giovinco serta Mirko Vucinic. Kondisi itu yang coba dimanfaatkan oleh La Beneamata untuk membujuk mantan pemain Napoli tersebut agar mau berkostum biru hitam. Bahkan Mediaset mengabarkan bahwa pihak Inter sudah menghubungi agen Quagliarella, Beppe Bozzo untuk melakukan pembicaraan soal kemungkinan kliennya pindah ke Giuseppe Meazza. Transfer ini mungkin saja terjadi. Pasalnya, Inter memang sudah lama dihubung hubungkan dengan Quagliarella sejak musim panas tahun lalu.</body>AAAAA<url>https_++soccer.sindonews.com+read+719945+56+inter-tawar-fabio-quagliarella-1361377464.html</url><title>Inter tawar Fabio Quagliarella</title><body>Sindonews.com Media di Italia, Mediaset melaporkan bahwa Inter Milan sudah mengajukan tawaran sebesar 7 juta poundsterling (setara Rp103 miliar) kepada Juventus. Nilai tawaran itu untuk memboyong Fabio Quagliarella pada bursa transfer musim panas mendatang</body>";

    char dest[2048];
    printf("%s", dest);  
    
    FILE *fp = fopen("kecil.txt", "r");

    char line[4096];
    char noUrl[4096];
    
    while(fgets(line, sizeof(line), fp)){
        // removeUrlTag(line, noUrl);
        takeStringBetweenTag(line, noUrl);
        printf("%s", noUrl);
    }

    // while(fgets(line, sizeof(line), fp)){
    //     removeUrlTag(line, noUrl);
    //     // takeStringBetweenTag(line, noUrl, "<body>", "</body>");
    //     printf("%s", noUrl);
    // }

    fclose(fp);
    
    return EXIT_SUCCESS;
}