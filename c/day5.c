/*
 * Good Solution from Reddit:
 *  https://www.reddit.com/r/adventofcode/comments/3viazx/day_5_solutions/cxo8886
 */
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


int p1_isnice(char *str, int len) {
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


int p2_isnice(char *str, int len) {
    int contains_match_pair = 0;
    int contains_sandwich = 0;
    for (int i = 0; i < len - 2; i++) {
        for (int j = i + 2; j < len-1; j++) {
            if ((str[i]   == str[j]) &&
                (str[i+1] == str[j+1]))
                contains_match_pair = 1;
        }
        if (str[i] == str[i+2]) {
            contains_sandwich = 1;
        }
    }
    return (contains_match_pair &&
            contains_sandwich);
}


int main() {
    FILE *fp = fopen("day5_input.txt", "r");
    char c;

    int p1_nice = 0;
    int p2_nice = 0;

    char *buf = malloc(sizeof(char) * MAX_LINE_SIZE);
    char *p = buf;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            if (p1_isnice(buf, (int)(p-buf))) {
                p1_nice++;
            }
            if (p2_isnice(buf, (int)(p-buf))) {
                p2_nice++;
            }
            p = buf;
            memset(buf, 0, MAX_LINE_SIZE);
        } else {
            *p++ = c;
        }
    }
    printf("Part I nice strings: %d\n", p1_nice);
    printf("Part II nice strings: %d\n", p2_nice);

    fclose(fp);
    free(buf);
    return 0;
}
