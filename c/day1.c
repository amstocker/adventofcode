#include "aoc.h"


int count_floor(char *in) {
    int floor = 0;
    for (int i=0, char c=in[0]; c != EOF; i++, c=in[i]) {
        switch (c) {
            case '(':
                floor++;
                break;
            case ')':
                floor--;
                break;
        }
    }
    return floor;
}


void part1(char *in) {
    printf("floor: %d\n", count_floor(in));
}

int main(int argc, char *argv[argc+1]) {
    char *in = input_open("day1_input.txt");
    
    part1(in);

    free(in);
    return 0;
}
