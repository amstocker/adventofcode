#include "aoc.h"


const long SEED = 20151125;
const int TARGET_ROW = 3010;
const int TARGET_COL = 3019;


#define NEXT(N) (((N) * 252533) % 33554393)

int main() {
    long code = SEED;
    int dir = 2;  // 1 := UP-RIGHT, 2 := DOWN-LEFT
    int row = 1, col = 1;
    for (;;) {
        code = NEXT(code);
        if (dir == 1) {
            if (row == 1) {
                dir = 2;
                col++;
            } else {
                row--;
                col++;
            }
        } else {
            if (col == 1) {
                dir = 1;
                row++;
            } else {
                row++;
                col--;
            }
        }
        if (row == TARGET_ROW && col == TARGET_COL) break;
    }
    printf("code @ (%i, %i) = %li\n", row, col, code);
}
