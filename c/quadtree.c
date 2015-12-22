#include "aoc.h"


static QTNode *QTNode_new(int x, int y, void *data) {
    QTNode *n = malloc(sizeof(QTNode));
    n->x = x;
    n->y = y;
    n->nw = NULL;
    n->ne = NULL;
    n->sw = NULL;
    n->se = NULL;
    n->parent = NULL;
    n->data = data;
    return n;
}


QTree *QTree_new() {
    QTree *qt = malloc(sizeof(QTree));
    qt->origin = NULL;
    return qt;
}


static void recursive_free(QTNode *n) {
    if (n->nw) {
        recursive_free(n->nw);
    }
    if (n->ne) {
        recursive_free(n->ne);
    }
    if (n->sw) {
        recursive_free(n->sw);
    }
    if (n->se) {
        recursive_free(n->se);
    }
    free(n);
}


void QTree_free(QTree *qt) {
    recursive_free(qt->origin);
    free(qt);
}


static QTNode *insert(QTNode *par, int nx, int ny, void *data) {
    if ((nx == par->x) && (ny == par->y)) {
        par->data = data;
        return par;
    }

#define QT_INSERT(dir)                              \
        if (par->dir) {                             \
            return insert(par->dir, nx, ny, data);  \
        } else {                                    \
            QTNode *new = QTNode_new(nx, ny, data); \
            par->dir = new;                         \
            new->parent = par;                      \
            return new;                             \
        }                                           \

#define QT_TRAVERSE(MACRO)                          \
    if ((nx > par->x) && (ny >= par->y)) {          \
        MACRO(ne);                                  \
    }                                               \
    else if ((nx >= par->x) && (ny < par->y)) {     \
        MACRO(se);                                  \
    }                                               \
    else if ((nx < par->x) && (ny <= par->y)) {     \
        MACRO(sw);                                  \
    }                                               \
    else if ((nx <= par->x) && (ny > par->y)) {     \
        MACRO(nw);                                  \
    }                                               \
    else {                                          \
        error("invalid coordinate");                \
        return NULL;                                \
    }

    QT_TRAVERSE(QT_INSERT)
}


QTNode *QTree_set(QTree *qt, int x, int y, void *data) {
    if (!qt->origin) {
        QTNode *n = QTNode_new(x, y, data);
        qt->origin = n;
        return n;
    }
    return insert(qt->origin, x, y, data);
}


static void *get(QTNode *par, int nx, int ny) {
    if ((nx == par->x) && (ny == par->y)) {
        return par->data;
    }

#define QT_GET(dir)                                 \
        if (par->dir) {                             \
            return get(par->dir, nx, ny);           \
        } else {                                    \
            return NULL;                            \
        }

    QT_TRAVERSE(QT_GET)
}


void *QTree_get(QTree *qt, int x, int y) {
    if (!qt->origin) {
        return NULL;
    }
    return get(qt->origin, x, y);
}
