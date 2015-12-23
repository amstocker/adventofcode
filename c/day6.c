#include "aoc.h"

#define MAX_LINE_LENGTH 128

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))


typedef enum {
    ON, OFF, TOGGLE
} OP;


int main() {
    FILE *fp = fopen("day6_input.txt", "r");
    char *box_fmt = "%d,%d through %d,%d\n";

    int p1_m[1000000] = {0};
    int p2_m[1000000] = {0};

    char line[MAX_LINE_LENGTH];
    int ofs, l, b, r, t;
    OP op;

    while (fgets(line, MAX_LINE_LENGTH, fp)) {

        if (strstr(line, "turn on") != NULL) {
            ofs = 8;
            op = ON;
        } else if (strstr(line, "turn off") != NULL) {
            ofs = 9;
            op = OFF;
        } else if (strstr(line, "toggle") != NULL) {
            ofs = 7;
            op = TOGGLE;        
        } else {
            error("invalid line");
        }
        sscanf(&line[ofs], box_fmt, &l, &b, &r, &t);

#define M(P, X, Y) (P##_m[1000*(X)+(Y)])

        for (int x = l; x < r + 1; x++) {
            for (int y = b; y < t + 1; y++) {
                switch (op) {
                    case ON:
                        M(p1, x, y) = 1;
                        M(p2, x, y)++;
                        break;
                    case OFF:
                        M(p1, x, y) = 0;
                        M(p2, x, y) = MAX(0, M(p2, x, y) - 1);
                        break;
                    case TOGGLE:
                        M(p1, x, y) = !M(p1, x, y);
                        M(p2, x, y) += 2;
                }
            }
        }
        memset(line, 0, MAX_LINE_LENGTH);
    }
    printf("Part I lights on: %d\n", int_array_sum(p1_m, 1000000));
    printf("Part II lights on: %d\n", int_array_sum(p2_m, 1000000));
}
