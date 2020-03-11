#include <stdlib.h>

typedef struct grp {
    double poids; //probabilité
    char* content;
    char* code;
    int longueur_code;
    struct grp* fils_gauche;
    struct grp* fils_droit;
} * groupe;

/**
 * Créer un groupe en mémoire avec les informations nécessaire pour
 * la gestion de ce dernier dans les futurs manipulation 
 */
groupe creer_groupe(double poids, char* content, groupe fils_gauche, groupe fils_droit);

void def_code(groupe groupe, char* code, int length);

/**
 * Fusionne deux groupe en un seul, place le groupe de poids 
 * le plus léger à gauche
 */
groupe fusionner_groupe(groupe groupe1, groupe groupe2);

/**
 * Retourne 1 si un groupe est un groupe d'origine (sans fusions de fils), 
 * 0 sinon
 */
int est_origine (groupe groupe);

/**
 * Libère de la mémoire, lui et ses enfants.
 */
void free_groupe(groupe groupe);

/**
 * Méthode d'affichage qui prend la forme d'un 
 * arbre tourné sur la gauche de 90°
 */
void afficher_groupe(int hauteur, groupe groupe);
