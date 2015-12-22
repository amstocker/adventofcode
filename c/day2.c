#include "aoc.h"


int wrapping_needed(int *arr) {
    int areas[] = { arr[0] * arr[1],
                    arr[1] * arr[2],
                    arr[2] * arr[0],
                    };
    return 2 * int_array_sum(areas, 3) + int_array_min(areas, 3);
}


int ribbon_needed(int *arr) {
    int *mins = int_array_mins(arr, 3, 2);
    return 2 * int_array_sum(mins, 2) + int_array_prod(arr, 3);
}


int main() {
    FILE *fp = fopen("day2_input.txt", "r");

    int wrapping_sum = 0;
    int ribbon_sum = 0;

    int t[3];
    while (fscanf(fp, "%dx%dx%d", &t[0], &t[1], &t[2]) != EOF) {
        wrapping_sum += wrapping_needed(t);
        ribbon_sum += ribbon_needed(t);
    }

    printf("wrapping: %d\n", wrapping_sum);
    printf("ribbon: %d\n", ribbon_sum);

    fclose(fp);
    return 0;
}
