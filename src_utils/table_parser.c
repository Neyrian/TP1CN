#include "table_parser.h"
#include <stdlib.h>

table get_empty_table() {
    table tbl = (table)malloc(sizeof(struct tbl));
    for (int i = 0; i < MAX_TABLE_SIZE; i++) tbl->letters[i] = NULL;
    tbl->nb_letters = 0;
    return tbl;
}

letter create_letter(char l, double p, double binf, double bsup) {
    letter ltr = (letter)malloc(sizeof(struct ltr));
    ltr->l = l;
    ltr->p = p;
    ltr->binf = binf;
    ltr->bsup = bsup;
    return ltr;
}

letter get_letter(table tbl, char l) {
    letter found = NULL;
    int nb_l = tbl->nb_letters;
    for (int i = 0; i < nb_l && found == NULL; i++)
        if (tbl->letters[i]->l == l)
            found = tbl->letters[i];
    return found;
}

letter get_letter_from_bornes(table tbl, double val) {
    int nb_l = tbl->nb_letters;
    for (int i = 0; i < nb_l; i++)
        if (tbl->letters[i]->binf <= val && tbl->letters[i]->bsup >= val)
            return tbl->letters[i];
    return NULL;
}

inline void add_letter(table tbl, letter ltr) {
    tbl->letters[tbl->nb_letters++] = ltr;
}

void free_table(table tbl) {
    int nb_l = tbl->nb_letters;
    for (int i = 0; i < nb_l; i++)
        free(tbl->letters[i]);
    free(tbl);
}

table parse_table_from_file(FILE * f) {
    int nb_letter = 0;
    char letter;
    float proba, binf, bsup;
    if(f == NULL) {
        fprintf(stderr,"Le descripteur de fichier est null ! Le fichier existe-t-il ?\n");
        exit(-1);
    }
    table tbl = get_empty_table();
    int res_c;
    while ((res_c = fscanf(f, "%c %f %f %f ", &letter, &proba, &binf, &bsup)) != EOF) {
        if (res_c < 4) break;
        tbl->letters[nb_letter++] = create_letter(letter, proba, binf, bsup);
    } 
    tbl->nb_letters = nb_letter;
    if(res_c < 4 && res_c != EOF) {
        fprintf(stderr,"Le contenu du fichier ne correspond pas à la forme :\n\
Char Proba Binf Bsup\n\
Char Proba Binf Bsup...\n");
        free_table(tbl);
        fclose(f);
        exit(-1);
    }
    return tbl;
}