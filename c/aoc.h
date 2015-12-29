/*
 * Advent of Code
 * ==============
 *
 */
#include <stdlib.h>
#include <stdio.h>
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
