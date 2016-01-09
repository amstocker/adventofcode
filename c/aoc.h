/*
 * Advent of Code
 * ==============
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <limits.h>


// error.c
void error(const char *msg);


// utils.c
int count_lines(FILE * fp);
int int_array_min(const int *array, const int len);
int *int_array_mins(const int *array, const int len, const int n);
int int_array_sum(const int *array, const int len);
int int_array_prod(const int *array, const int len);


// qtree.c
typedef struct QTNode {
    int x;
    int y;
    struct QTNode *nw;
    struct QTNode *ne;
    struct QTNode *sw;
    struct QTNode *se;
    struct QTNode *parent;
    void *data;
} QTNode;

typedef struct {
    QTNode *origin;
} QTree;

QTree *QTree_new();
void QTree_free(QTree *qt);
QTNode *QTree_set(QTree *qt, int x, int y, void *data);
void *QTree_get(QTree *qt, int x, int y);


// map.c
#define INIT_SIZE 16
#define TOMBSTONE ((void *)-1)
#define REHASH_SIZE 0.7

typedef uint32_t (*Map_hash_func_t) (char*);

typedef struct Map {
    char **key;
    void **val;
    int size;
    int nelem;
    int nused;
} Map;

Map *Map_new();
void Map_free(Map *m);
void __map_put(Map *m, char *key, void *val);
void *__map_get(Map *m, char *key);
void *__map_remove(Map *m, char *key);

#define Map_put(M, K, V) __map_put((M), (char *)(K), (V));
#define Map_get(M, K) __map_get((M), (char *)(K))
#define Map_remove(M, K) __map_remove((M), (char *)(K))


// set.c
typedef Map Set;

Set *Set_new();
void Set_free(Set *s);
void Set_add(Set *s, char *v);
int Set_check(Set *s, char *v);
char *Set_remove(Set *s, char *v);
char **Set_iter(Set *s);
