#include "aoc.h"


static int MARKER = 1;

int main() {
    FILE *fp = fopen("day3_input.txt", "r");
    char c;

    QTree *qt = QTree_new();
    QTree_set(qt, 0, 0, &MARKER);
    
    int p1_unique = 1;
    int x = 0, y = 0;
    void *get;
    while ((c = fgetc(fp)) != EOF) {
        switch(c) {
            case '>': x++; break;
            case '^': y++; break;
            case '<': x--; break;
            case 'v': y--; break;
            default:
                continue;
        }
        get = QTree_get(qt, x, y);
        if ((get != NULL) && (*(int*)get == MARKER)) {
            continue;
        } else {
          QTree_set(qt, x, y, &MARKER);
          p1_unique++;
        }
    }
    printf("part I unique: %d\n", p1_unique);
    QTree_free(qt);
    return 0;
}
