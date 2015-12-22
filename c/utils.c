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
        } else str++;
    }
    return count;
}


int int_array_min(const int *array, const int len) {
    int mele = array[0];
    for (int i = 1; i < len; i++) {
        if (array[i] < mele) {
            mele = array[i];
        }
    }
    return mele;
}


int *int_array_mins(const int *array, const int len, const int n) {
    assert(n <= len);
    int *mins = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        mins[i] = INT_MAX;
    }
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < n; j++) {
            if (array[i] < mins[j]) {
                for (int k = n-1; k > j; k--) {
                    mins[k] = mins[k-1];
                }
                mins[j] = array[i];
                break;
            }
        }
    }
    return mins;
}


int int_array_sum(const int *array, const int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += array[i];
    }
    return sum;
}


int int_array_prod(const int *array, const int len) {
    int prod = 1;
    for (int i = 0; i < len; i++) {
        prod *= array[i];
    }
    return prod;
}
