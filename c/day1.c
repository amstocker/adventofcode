#include "aoc.h"


int find_floor(char *in) {
    int floor = 0;
    while (*in) {
        switch (*in++) {
            case '(': floor++; break;
            case ')': floor--; break;
        }
    }
    return floor;
}


int find_ground_floor(char *in) {
    int floor = 0;
    int index = 0;
    while (*in) {
        index ++;
        switch (*in++) {
            case '(': floor++; break;
            case ')': floor--; break;
        }
        if (floor == -1) break;
    }
    return index;
}


void part1(char *in) {
    printf("floor: %d\n", find_floor(in));
}


void part2(char *in) {
    printf("ground floor: %d\n", find_ground_floor(in));
}


int main(int argc, char *argv[argc+1]) {
    
    char *in = input_open("day1_input.txt");
    
    part1(in);
    part2(in);

    free(in);
    return 0;
}
