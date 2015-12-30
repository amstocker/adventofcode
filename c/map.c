#include "aoc.h"

#define INIT_SIZE 16
#define TOMBSTONE ((void *)-1)
#define REHASH_SIZE 0.7


static inline uint32_t fnv_hash(char *p) {
    uint32_t r = 2166136261;
    for (; *p; p++) {
        r ^= *p;
        r *= 16777619;
    }
    return r;
}


static inline uint32_t djb2_hash(char *p) {
    uint32_t r = 5381;
    for (; *p; p++) {
        r = ((r << 5) + r) + *p;
    }
    return r;
}


Map *Map_new() {
    Map *m = malloc(sizeof(Map));
    m->key = calloc(INIT_SIZE, sizeof(char *));
    m->val = calloc(INIT_SIZE, sizeof(void *));
    m->size = INIT_SIZE;
    m->nelem = 0;
    m->nused = 0;
    return m;
}


void Map_free(Map *m) {
    free(m->key);
    free(m->val);
    free(m);
}


static void maybe_rehash(Map *m) {
    if (m->nused < m->size * REHASH_SIZE) {
        return;
    }
    int newsize = (m->nelem < m->size * 0.35) ? m->size : m->size * 2;
    char **k = calloc(newsize, sizeof(char *));
    void **v = calloc(newsize, sizeof(void *));
    int mask = newsize - 1;
    for (int i = 0; i < m->size; i++) {
        if (m->key[i] == NULL || m->key[i] == TOMBSTONE) {
            continue;
        }
        int j = fnv_hash(m->key[i]) & mask;
        for (;; j = (j + 1) & mask) {
            if (k[j] != NULL) {
                continue;
            }
            k[j] = m->key[i];
            v[j] = m->val[i];
            break;
        }
    }
    free(m->key);
    free(m->val);
    m->key = k;
    m->val = v;
    m->size = newsize;
    m->nused = m->nelem;
}


void __map_put(Map *m, char *key, void *val) {
    maybe_rehash(m);
    int mask = m->size - 1;
    int i = fnv_hash(key) & mask;
    for (;; i = (i + 1) & mask) {
        char *k = m->key[i];
        if (k == NULL || k == TOMBSTONE) {
            m->key[i] = key;
            m->val[i] = val;
            m->nelem++;
            if (k == NULL) {
                m->nused++;
            }
            return;
        }
        if (!strcmp(k, key)) {
            m->val[i] = val;
            return;
        }
    }
}


void *__map_get(Map *m, char *key) {
    int mask = m->size - 1;
    int i = fnv_hash(key) & mask;
    for (; m->key[i] != NULL; i = (i + 1) & mask) {
        if (m->key[i] != TOMBSTONE && !strcmp(m->key[i], key)) {
            return m->val[i];
        }
    }
    return NULL;
}


void *__map_remove(Map *m, char *key) {
    int mask = m->size - 1;
    int i = fnv_hash(key) & mask;
    for (; m->key[i] != NULL; i = (i + 1) & mask) {
        if (m->key[i] == TOMBSTONE || strcmp(m->key[i], key)) {
            continue;
        }
        m->key[i] = TOMBSTONE;
        void *r = m->val[i];
        m->val[i] = NULL;
        m->nelem--;
        return r;
    }
    return NULL;
}
