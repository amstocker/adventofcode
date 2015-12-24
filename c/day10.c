#include "aoc.h"


char *iter(char *seed) {

    // calculate length of new string
    int size = 0;
    int group_size = 1;
    char buf[32] = {0};
    char *p = seed;
    while (*++p) {
        if (*p == *(p-1)) {
            group_size++;
        } else {
            sprintf(buf, "%d", group_size);
            size += (strlen(buf)+1);
            group_size = 1;
            memset(buf, 0, sizeof(buf));
        }
    }
    if (group_size > 0) {
        size += (strlen(buf)+1);
    }
    group_size = 1;
    memset(buf, 0, sizeof(buf));
    
    // create new string    
    char *new = calloc(size+1, sizeof(char));
    char *np = new;

    p = seed;
    char last = *p;
    while (*++p) {
        if (*p == *(p-1)) {
            group_size++;
        } else {
            sprintf(buf, "%d", group_size);
            group_size = 1;
            strcpy(np, buf);
            np += strlen(buf);
            
            *np = last;
            np++;
            last = *p;

            memset(buf, 0, sizeof(buf));
        }
    }
    if (group_size > 0) {
        sprintf(buf, "%d", group_size);
        strcpy(np, buf);
        np += strlen(buf);
        *np = last;
    } else {
        *np = '1';
        np++;
        *np = last;
    }
    printf("size: %i, ptrdiff: %i\n", size, (int)(np-new));
    
    free(seed);
    return new;
}


int main() {
    const char *start = "3113322113";
    
    char *seed = calloc(sizeof(start), 1);
    strcpy(seed, start);

    for(int i = 0; i < 20; i++) {
        printf("length: %zu @ iter %i\n", strlen(seed), i);
        printf("seed: %s\n", seed);
        seed = iter(seed);
    }
    printf("final length: %zu\n", strlen(seed));

    free(seed);
    return 0;
}
