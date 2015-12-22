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
        
        // parse line into 3-tuple and memcpy to array
        int tup[3];
        if (sscanf(buf, "%dx%dx%d", &tup[0], &tup[1], &tup[2]) == EOF) {
            error("error scanning list of package sizes");
        }
        memcpy(ptr, tup, sizeof(int) * 3);
        ptr += 3;
        
        if (*in == '\n') {
            in++;
        }
    }
    return tuples;
}


int pt1_wrapping_needed(int *array) {
    int *tmp = array;
    int l = *tmp++,
        w = *tmp++,
        h = *tmp;
    int areas[] = { l*w, w*h, h*l };
    return 2 * int_array_sum(areas, 3) + int_array_min(areas, 3);
}


void part1(int* tuples, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += pt1_wrapping_needed(tuples);
        tuples += 3;
    }
    printf("part I sum: %d\n", sum);
}


int main(int argc, char *argv[argc+1]) {
    char *in = input_open("day2_input.txt");
    int nlines = str_count_lines(in);
    int *tuples = make_3tuples(in, nlines);

    part1(tuples, nlines);

    free(in);
    free(tuples);
    return 0;
}
