#include "aoc.h"

#define PLACEHOLDER ((void*) 1)


Set *Set_new() {
    return (Set*)Map_new();
}

void Set_free(Set *s) {
    Map_free((Map*)s);
}

void Set_add(Set *s, char *v) {
    Map_put((Map*)s, v, PLACEHOLDER);
}

int Set_check(Set *s, char *v) {
    return Map_get((Map*)s, v) ? 1 : 0;
}

char *Set_remove(Set *s, char *v) {
    return Map_remove((Map*)s, v) ? v : NULL;
}

char **Set_iter(Set *s) {
    char **keys = calloc(s->nelem, sizeof(char*));
    char **p = keys;
    for (int i = 0; i < s->size; i++) {
        if (s->key[i] != NULL && s->key[i] != TOMBSTONE) {
            *p++ = s->key[i];
        }
    }
    return keys;
}
