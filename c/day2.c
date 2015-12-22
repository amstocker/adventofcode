#include "aoc.h"

#define BUF_SIZE 256


int *make_3tuples(char* in, int len) {
    
    int *tuples = malloc(sizeof(int) * 3 * len);
    int *ptr = tuples;
    
    char *start;
    char buf[BUF_SIZE];
    while (*in) {
        start = in;
        while(*in != '\n' && *in != '\0') {
            in++;
        }
        if ((int)(in-start) > (BUF_SIZE-1)) {
            error("max line length exceeded");
        }
        
        memset(buf, 0, sizeof(buf));
        memcpy(buf, start, (int)(in-start));
        buf[BUF_SIZE - 1] = '\0';
        
        if (sscanf(buf, "%dx%dx%d", ptr, ptr+1, ptr+2) == EOF) {
            error("error scanning list of package sizes");
        }
        ptr += 3;
        
        if (*in == '\n') {
            in++;
        }
    }
    return tuples;
}


int wrapping_needed(int l, int w, int h) {
    int areas[] = { l*w, w*h, h*l };
    return 2 * int_array_sum(areas, 3) + int_array_min(areas, 3);
}


int ribbon_needed(int *array) {
    int *mins = int_array_mins(array, 3, 2);
    return 2 * int_array_sum(mins, 2) + int_array_prod(array, 3);
}


void part1(int* tuples, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += wrapping_needed(tuples[0], tuples[1], tuples[2]);
        tuples += 3;
    }
    printf("part I sum: %d\n", sum);
}


void part2(int* tuples, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += ribbon_needed(tuples);
        tuples += 3;
    }
    printf("part II sum: %d\n", sum);
}


int main(int argc, char *argv[argc+1]) {
    char *in = input_open("day2_input.txt");
    int nlines = str_count_lines(in);
    int *tuples = make_3tuples(in, nlines);

    part1(tuples, nlines);
    part2(tuples, nlines);

    free(in);
    free(tuples);
    return 0;
}
