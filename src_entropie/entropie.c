#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ELEMS_SIZE 32

inline double log2(double value) {
    return log(value)/log(2);
}

typedef struct {
    int nb_elems;
    double elems[MAX_ELEMS_SIZE];
} s_source, *source;

source parse_file(char* file_name) {
    FILE *f ;
    int nb_elems = 0;
    double elem;
    f = fopen(file_name, "r");
    if(f == NULL) {
        fprintf(stderr,"Aucun fichiers de ce nom !\n");
        exit(-1);
    }
    source S = (source) malloc(sizeof(s_source));
    int res_c;
    while ((res_c = fscanf(f, "%lf", &elem)) != EOF) {
        if (res_c == 0) break;
        S->elems[nb_elems++] = elem;
    } 
    S->nb_elems = nb_elems;
    fclose(f);
    if(res_c == 0) {
        fprintf(stderr,"Le contenu du fichier est erroné !\n");
        free(S);
        exit(-1);
    }
    return S;
}

void afficher_src (source S) {
    printf("contenu de la source S : {");
    for(int i = 0; i < S->nb_elems; i++) {
        printf("%.2lf", S->elems[i]);
        if (i < S->nb_elems - 1) printf(", ");
    }
    printf("}\n");
}

double calcul_entropie(source S) {
    double resultat = 0;
    for(int i = 0; i < S->nb_elems; i++) {
        resultat += -S->elems[i]*log2(S->elems[i]);
    }
    return resultat;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Veuillez indiquer un nom de fichier.\n");
        exit(-1);
    }

    source S = parse_file(argv[1]);

    afficher_src(S);
    printf("Entropie de S, H(S) = %lf\n", calcul_entropie(S));
    
    free(S);

    return EXIT_SUCCESS;
}