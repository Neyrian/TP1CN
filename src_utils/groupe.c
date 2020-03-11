#include "groupe.h"
#include <stdio.h>

groupe creer_groupe(double poids, char* content, groupe fils_gauche, groupe fils_droit) {
    groupe group = (groupe) malloc(sizeof(struct grp));
    group->poids = poids;
    group->content = content;
    group->fils_gauche = fils_gauche;
    group->fils_droit = fils_droit;
    group->code = NULL;
    group->longueur_code = 0;
    return group;
}

void def_code(groupe groupe, char* code, int length) {
    groupe->code=code;
    groupe->longueur_code=length;
}

groupe fusionner_groupe(groupe groupe1, groupe groupe2) {
    double poids_total = groupe1->poids + groupe2->poids;
    if (groupe1->poids <= groupe2->poids)
        return creer_groupe(poids_total, NULL, groupe1, groupe2);
    else
        return creer_groupe(poids_total, NULL, groupe2, groupe1);
}

int est_origine (groupe groupe) {
    if (groupe != NULL && groupe->fils_gauche == NULL && groupe->fils_droit == NULL) {
        return 1;
    }
    return 0;
}

void free_groupe(groupe groupe) {
    if (groupe != NULL) {
        free (groupe->content);
        free (groupe->code);
        free_groupe (groupe->fils_gauche);
        free_groupe (groupe->fils_droit);
        free (groupe);
    }
}

void afficher_groupe(int hauteur, groupe groupe) {
    if (groupe != NULL) {
        afficher_groupe(hauteur + 1, groupe->fils_droit);
        for(int i = 0; i < hauteur; i++) printf("\t");
        printf("%f ", groupe->poids);
        if (groupe->code != NULL) printf("[%s] ", groupe->code); 
        if (est_origine(groupe)) {
            printf("%s", groupe->content);
        }
        printf("\n");
        afficher_groupe(hauteur + 1, groupe->fils_gauche);
    }
}