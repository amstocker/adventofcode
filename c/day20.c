#include "aoc.h"


//const long LIMIT = 29000000;
const long LIMIT = 1000;


long present_count(long house) {
    long sum = house;
    for (long i = 1; i <= house / 2; i++) {
        if (house % i == 0) {
            sum += i;
        }
    }
    return sum * 10;
}


int main() {
    long cnt;
    for (long i = 1;; i++) {
        cnt = present_count(i);
        printf("house %li got %li presents.\n", i, cnt);
        if (cnt >= LIMIT) {
            break;
        }
    }
}
