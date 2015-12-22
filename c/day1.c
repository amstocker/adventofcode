#include "aoc.h"


int main() {
    FILE *fp = fopen("day1_input.txt", "r");
    char c;

    int floor = 0;
    int index = 0;

    while ((c = fgetc(fp)) != EOF) {
        switch(c) {
            case '(': floor++; break;
            case ')': floor--; break;
        }
        index++;
        if (floor == -1) {
            printf("first basement level (-1): %d\n", index);
        }
    }
    printf("final floor: %d\n", floor);

    return 0;
}
