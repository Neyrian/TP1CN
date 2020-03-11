#include <stdio.h>
#include "../src_utils/collection.h"

#ifndef _GROUPE_H_
#define _GROUPE_H_
#include "../src_utils/groupe.h"
#endif /* _GROUPE_H_ */

collec col; //variable globale pour créer l'arbre de huffman.

void parse_file(char* filename, int mult);
void parse_file_worker(FILE * f, char* name, double val, int calls);
void construire_huffman();
void definir_code_huffman(groupe racine, char* code, int code_length);
void afficher_table_huffman(groupe racine);
double calc_lg_moy_huffman(groupe racine);

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "usage : %s <fichier_source> <multiplicité>\n", argv[0]);
        exit(-1);
    }

    //On initialise la collection d'éléments
    col = get_collec();
    //On remplit la collection avec les fichiers d'entrée
    int mult = atoi(argv[2]);
    if (mult < 1) {
        fprintf(stderr, "Multiplicité incorrecte\n");
        destroy_collec(col);
        exit(-1);
    }
    parse_file(argv[1], mult);
    
    //Construit l'arbre de Huffman
    construire_huffman();
    groupe racine = get(col, get_lowest(col));
    //Définit le code associé à chaque noeud
    definir_code_huffman(racine, NULL, 0);

    //Affichage de l'arbre des événements.
    afficher_groupe(0, racine); 

    //Affichage des codes des événements.
    printf("\nContenu de la table de codage :\n");
    afficher_table_huffman(racine);

    //Affichage de la longueurs moyenne des codes.
    printf("\nLongueur moyenne du code = %f\n", calc_lg_moy_huffman(racine) / atoi(argv[2]));

    //On détruit la collection et les éléments qui la compose (free)
    destroy_collec(col);
    return EXIT_SUCCESS;
}

void parse_file(char* filename, int mult) {
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        fprintf(stderr,"Le descripteur de fichier est null ! Le fichier existe-t-il ?\n");
        destroy_collec(col);
        exit(-1);
    }
    char* name = NULL;
    double elem;
    int n = 1;
    int res_c;
    unsigned long last_pos;
    while ((res_c = fscanf(f, "%lf", &elem)) != EOF) {
        if (res_c == 0) break;
        fflush(f);
        last_pos = ftell(f);
        name = malloc(16);
        sprintf(name, "e%d", n);
        parse_file_worker(f, name, elem, mult);
        fseek(f, last_pos, SEEK_SET);
        free(name);
        n++;
    }
    fclose(f);
    if(res_c == 0) {
        fprintf(stderr,"Contenu du fichier erroné !\n");
        destroy_collec(col);
        exit(-1);
    }
}

void parse_file_worker(FILE * f, char* name, double val, int calls) {
    if (calls > 1) {
        fseek(f, 0, SEEK_SET);
        double elem;
        int n = 1;
        int offset = 0;
        for(; name[offset] != '\0'; offset++) {}
        unsigned long last_pos;
        int res_c;
        while ((res_c = fscanf(f, "%lf", &elem)) != EOF) {
            if (res_c == 0) break;
            //On rajoute le nom de l'événement dans le nom actuel.
            sprintf(name+offset, "e%d%c", n, '\0');
            //On sauvegarde la position actuelle et on fait l'appel récursif.
            fflush(f);
            last_pos = ftell(f);
            parse_file_worker(f, name, elem*val, calls - 1);
            //On passe à l'événement suivant en réstaurant la position.
            fseek(f, last_pos, SEEK_SET);
            n++;
        }
        if(res_c == 0) {
            fprintf(stderr,"Contenu du fichier erroné !\n");
            destroy_collec(col);
            exit(-1);
        }
    } else {
        int len = 0;
        for(; name[len] != '\0'; len++) {}
        char* actual_name = malloc(len+1);
        for(int i = 0; i <= len; i ++) actual_name[i] = name[i];
        add(col, creer_groupe(val, actual_name, NULL, NULL));
    }
}

/**
 * Méthode la plus couteuse à cause de get_lowest et du add
 * compléxité de O(n^(2t))
 */
void construire_huffman() {
    groupe tmp1, tmp2;
    while(nb_elems(col) != 1) {
        tmp1 = remove_elem(col, get_lowest(col));
        tmp2 = remove_elem(col, get_lowest(col));
        add(col, fusionner_groupe(tmp1, tmp2));
    }
}

void definir_code_huffman(groupe racine, char* code, int code_length) {
    char* code_tmp = NULL;
    if (racine != NULL) {
        //on définit le code du noeud courant
        def_code(racine, code, code_length);

        //on définit le code pour le fils droit
        code_tmp = malloc(code_length+2);
        code_tmp[code_length+1] = '\0';
        for(int i = 0; i < code_length; i++) code_tmp[i] = code[i];
        code_tmp[code_length] = '1';
        definir_code_huffman(racine->fils_droit, code_tmp, code_length + 1);

        //on définit le code pour le fils gauche
        code_tmp = malloc(code_length+2);
        code_tmp[code_length+1] = '\0';
        for(int i = 0; i < code_length; i++) code_tmp[i] = code[i];
        code_tmp[code_length] = '0';
        definir_code_huffman(racine->fils_gauche, code_tmp, code_length + 1);
    } else {
        if (code!=NULL) free(code);
    }
}

void afficher_table_huffman(groupe racine) {
    if (racine != NULL) {
        if (est_origine(racine)) {
            printf("%s | %s\n", racine->content, racine->code);
        }
        afficher_table_huffman(racine->fils_droit);
        afficher_table_huffman(racine->fils_gauche);
    }
}

double calc_lg_moy_huffman(groupe racine) {
    if (racine != NULL) {
        if (est_origine(racine)) {
            return (racine->poids * racine->longueur_code);
        } else {
            return calc_lg_moy_huffman(racine->fils_gauche) + calc_lg_moy_huffman(racine->fils_droit);
        }
    }
    return 0;
}