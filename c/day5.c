#include "aoc.h"

const int LINE_SIZE = 16;


int isvowel(char c) {
    switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u': return 1;
        default: return 0;
    }
}


int isnice(char *str) {
    int vowel_count = 0;
    int contains_dbl = 0;

#define CMP(I, A, B) ((str[(I)] == (A)) && (str[(I)+1] == (B)))

    for (int i = 0; i < LINE_SIZE - 1; i++) {
       if (CMP(i, 'a', 'b') ||
           CMP(i, 'c', 'd') ||
           CMP(i, 'p', 'q') ||
           CMP(i, 'x', 'y'))
           return 0;
       if (str[i] == str[i+1]) {
           contains_dbl = 1;
       }
       if (isvowel(str[i])) {
           vowel_count++;
       }
    }
    if (isvowel(str[LINE_SIZE-1])) {
        vowel_count++;
    }
    return ((vowel_count >= 3) && contains_dbl);
}


int main() {
    FILE *fp = fopen("day5_input.txt", "r");
    char c;

    int nice = 0;

    char *buf = malloc(sizeof(char) * LINE_SIZE);
    char *p = buf;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            if (isnice(buf)) nice++;
            p = buf;
        } else {
            *p++ = c;
        }
    }
    printf("nice strings: %d\n", nice);

    fclose(fp);
    free(buf);
    return 0;
}
