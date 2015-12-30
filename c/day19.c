#include "aoc.h"


int main() {
    Map *m = Map_new();

    char *str = "fdsjkfsdjjklfsaddsfa";
    Map_put(m, "abc", str);
    str = Map_get(m, "abc");
    printf("res: %s\n", str);
    Map_free(m);
    return 0;
}
