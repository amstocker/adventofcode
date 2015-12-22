#include "aoc.h"


int str_count_lines(const char *str) {
    int count = 1;
    while (*str) {
        if (*str == '\n') {
            str++;
            if (*str == '\0') {
                break;
            } else {
                count++;
            }
            str--;
        }
        str++;
    }
    return count;
}


int int_array_min(const int *array, const int len) {
    int mele = *array;
    for (int i = 1; i < len; i++) {
        array++;
        if (*array < mele) {
            mele = *array;
        }
    }
    return mele;
}


int int_array_sum(const int *array, const int len) {
    int sum = 0;
    for(int i = 0; i < len; i++) {
        sum += *array;
        array++;
    }
    return sum;
}
