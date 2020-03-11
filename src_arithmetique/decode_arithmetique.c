#include <stdlib.h>
#include <stdio.h>
#include <math.h> //Pour modf
#include "../src_utils/table_parser.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage : %s <fichier table> <code optimisé>\n", argv[0]);
        exit(-1);
    }

    //Ouverture du fichier et création de la table
    FILE *f = fopen(argv[1], "r");
    table table = parse_table_from_file(f);
    fclose(f);

    //On enregistre le message
    double Vmessage = atof(argv[2]);
    double nb_chars;
    //On sépare la partie entière de la partie réelle
    Vmessage = modf(Vmessage, &nb_chars);
    if (Vmessage == (double)0.0) {
        fprintf(stderr, "Le code est erroné.\n");
        free_table(table);
        exit(-1);
    }

    //Decodage arithmétique
    for(int i = 0; i < nb_chars; i++) {
        letter letter = get_letter_from_bornes(table, Vmessage);
        Vmessage = (Vmessage - letter->binf) / letter->p;
        printf("%c", letter->l);
    }
    printf("\n");

    free_table(table);
    return EXIT_SUCCESS;
}