#include <stdlib.h>
#include <stdio.h>
#include "../src_utils/table_parser.h"

int main(int argc, char* argv[]) {
    if (argc != 3 || *argv[2] == '\0') {
        fprintf(stderr, "usage : %s <fichier table> <message>\n", argv[0]);
        exit(-1);
    }

    //Ouverture du fichier et création de la table
    FILE *f = fopen(argv[1], "r");
    table table = parse_table_from_file(f);
    fclose(f);

    //On enregistre le message
    char * message = argv[2];
    int nb_chars = 0;
    for (int i = 0; message[i] != '\0'; i++) nb_chars++;

    //Codage arithmétique
    float Binf = 0.f, Bsup = 1.f;
    float Vmessage = 1.f;
    float Vecart = Bsup - Binf;
    for(int i = 0; i < nb_chars; i++) {
        letter letter = get_letter(table, message[i]);
        if (letter == NULL) {
            fprintf(stderr, "Le message contient des lettres absentes dans la table.\n");
            free_table(table);
            exit(-1);
        }
        Bsup = Binf + Vecart * letter->bsup;
        Binf = Binf + Vecart * letter->binf;
        Vecart = Bsup - Binf;
    }
    Vmessage = (Bsup + Binf) / 2;

    //Affichage du résultat :
    printf("Valeur du message : %f\n", Vmessage);
    printf("Valeur du message optimisé : %f\n", Vmessage + nb_chars);

    free_table(table);
    return EXIT_SUCCESS;
}