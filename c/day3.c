#include "aoc.h"


// useless number to store in quadtree
static int MARKER = 2497199;


void maybe_update(QTree *qt, int x, int y, int *unique) {
    void *get = QTree_get(qt, x, y);
    if ((get == NULL) || (*(int*)get != MARKER)) {
        QTree_set(qt, x, y, &MARKER);
        (*unique)++;
    }
}


int main() {
    FILE *fp = fopen("day3_input.txt", "r");
    char c;

    // part I
    QTree *p1_qt = QTree_new();
    QTree_set(p1_qt, 0, 0, &MARKER);
    int p1_unique = 1;
    int p1_x = 0, p1_y = 0;

    // part II
    QTree *p2_qt = QTree_new();
    QTree_set(p2_qt, 0, 0, &MARKER); 
    int p2_unique = 1;
    int p2_sx = 0, p2_sy = 0;  // santa
    int p2_rx = 0, p2_ry = 0;  // robo-santa
    int isrobo = 0;

    while ((c = fgetc(fp)) != EOF) {
        switch(c) {
            case '>':
                p1_x++;
                if (isrobo) p2_rx++; else p2_sx++;
                break;
            case '^':
                p1_y++;
                if (isrobo) p2_ry++; else p2_sy++;
                break;
            case '<':
                p1_x--;
                if (isrobo) p2_rx--; else p2_sx--;
                break;
            case 'v':
                p1_y--;
                if (isrobo) p2_ry--; else p2_sy--;
                break;
            default:
                continue;
        }

        // part I
        maybe_update(p1_qt, p1_x, p1_y, &p1_unique);

        // part II
        maybe_update(p2_qt, p2_sx, p2_sy, &p2_unique);  // santa
        maybe_update(p2_qt, p2_rx, p2_ry, &p2_unique);  // robo-santa
        isrobo = !isrobo;
    }
    printf("part I unique: %d\n", p1_unique);
    printf("part II unique: %d\n", p2_unique);
    
    QTree_free(p1_qt);
    QTree_free(p2_qt);
    
    fclose(fp);
    return 0;
}
