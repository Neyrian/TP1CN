#ifndef _GROUPE_H_
#define _GROUPE_H_
#include "groupe.h"
#endif /* _GROUPE_H_ */

#define COLLEC_SIZE 46656 //6⁶

typedef struct collection{
    int elems;
    groupe collection[COLLEC_SIZE];
} *collec;

/**
 * Initialise et Reset la collection puis la donne.
 */
collec get_collec();

/**
 * ajoute un groupe dans la collection et renvoit son indice
 */
int add(collec col, groupe elem);

/**
 * enlève l'elem correspondant.
 */
groupe remove_elem(collec col, int index);

/**
 * renvoit le nombre d'éléments présents dans la collec.
 */
int nb_elems(collec col);

int get_lowest(collec col);

groupe get(collec col, int index);

void destroy_collec(collec col);