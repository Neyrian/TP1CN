#ifndef _COLLECTION_H_
#define _COLLECTION_H_
#include "collection.h"
#endif /* _COLLECTION_H_ */

collec get_collec() {
    collec col = (collec)malloc(sizeof(struct collection));
    for(int i = 0; i < COLLEC_SIZE; i++) {
        col->collection[i] = NULL;
    }
    col->elems = 0;
    return col;
}

int add(collec col, groupe elem) {
    if (col->elems == COLLEC_SIZE) return -1;
    int i = 0;
    for(; i < COLLEC_SIZE && col->collection[i] != NULL; i++) {}
    col->collection[i] = elem;
    col->elems++;
    return i;
}

groupe remove_elem(collec col, int index) {
    groupe res = col->collection[index];
    col->collection[index] = NULL;
    col->elems--;
    return res; //NULL si l'index était incorrect.
}

int nb_elems(collec col) {
    return col->elems;
}

int get_lowest(collec col) {
    groupe min = NULL;
    int index_min = -1;
    for (int i = 0; i < COLLEC_SIZE; i++) {
        if (col->collection[i] != NULL) {
            if (min==NULL) {
                min = col->collection[i];
                index_min = i;
            } 
            if (min->poids > col->collection[i]->poids) {
                min = col->collection[i];
                index_min = i;
            }
        }
    }
    return index_min;
}

groupe get(collec col, int index) {
    return col->collection[index];
}

void destroy_collec(collec col) {
    for(int i = 0; i < COLLEC_SIZE; i ++) {
        if (col->collection[i] != NULL) {
            free_groupe (col->collection[i]);
        }
    }
    free(col);
}