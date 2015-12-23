#include "aoc.h"

const int MAX_LINE_SIZE = 64;


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


int isnice(char *str, int len) {
    int vowel_count = 0;
    int contains_dbl = 0;

#define CMP(I, A, B) ((str[(I)] == (A)) && (str[(I)+1] == (B)))

    for (int i = 0; i < len - 1; i++) {
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
    if (isvowel(str[len-1])) {
        vowel_count++;
    }
    return ((vowel_count >= 3) && contains_dbl);
}


int main() {
    FILE *fp = fopen("day5_input.txt", "r");
    char c;

    int nice = 0;

    char *buf = malloc(sizeof(char) * MAX_LINE_SIZE);
    char *p = buf;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            if (isnice(buf, (int)(p-buf))) {
                nice++;
            }
            p = buf;
            memset(buf, 0, MAX_LINE_SIZE);
        } else {
            *p++ = c;
        }
    }
    printf("nice strings: %d\n", nice);

    fclose(fp);
    free(buf);
    return 0;
}
