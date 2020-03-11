#include <stdio.h>

#define MAX_TABLE_SIZE 64 

typedef struct ltr *letter;

typedef struct tbl {
    letter letters[64];
    int nb_letters;
} *table;

typedef struct ltr {
    char l; //lettre
    float p; //probabilité
    float binf, bsup; //borne inférieur et supérieur
} *letter;

/**
 * initialise et donne une table vide
 */
table get_empty_table();

/**
 * Créer une lettre depuis les infos nécessaire
 */
letter create_letter(char l, double p, double binf, double bsup);

/**
 * récupère une lettre de la table depuis le character
 */
letter get_letter(table tbl, char l);

/**
 * récupère une lettre de la table qui se trouve dans les bornes
 */
letter get_letter_from_bornes(table tbl, double val);

/**
 * Ajoute une lettre à la table
 */
void add_letter(table tbl, letter ltr);

/**
 * Libère la table et ses éléments de la mémoire
 */
void free_table(table tbl);

/**
 * Parse a file into a table from a file descriptor
 * le fichier f est ouver en lecture
 */
table parse_table_from_file(FILE * f);