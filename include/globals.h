#ifndef GLOBALS_H
#define GLOBALS_H

#define MAX_WORD_PER_ALPHABETS 15000;
#define MAX_WORD_LEN
#define ALPHABET_SIZE 26

typedef struct {
    char abjad;
    int panjangKata;
    char kata[MAX_WORD_LEN];
    int frekuensi;
} StoringWordsInfo;

extern StoringWordsInfo listKataPerHuruf[ALPHABET_SIZE][MAX_WORD_PER_ALPHABETS];
extern int jumlahKataPerAbjad[ALPHABET_SIZE] = {0};

#endif 