#include "aoc.h"

#define BIT_SET(a,b)   ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b)  ((a) ^= (1<<(b)))
#define BIT_CHECK(a,b) ((a) & (1<<(b)))

static const int SIZE = sizeof(unsigned int);


unsigned int permute(unsigned int seed) {
    BIT_FLIP(seed, 0);
    int bit = 0;
    while (!BIT_CHECK(seed, bit)) {
        bit++;
        BIT_FLIP(seed, bit);
    }
    return seed;
}


int *create_array(FILE *fp, int len) {
    int *arr = calloc(len, sizeof(int));
    int elem;
    for (int i = len - 1; i >= 0; i--) {
        fscanf(fp, "%i", &elem);
        arr[i] = elem;
    }
    return arr;
}


int main() {
    FILE *fp = fopen("day24_input.txt", "r");
    int len = count_lines(fp);
    int *arr = create_array(fp, len);
}
