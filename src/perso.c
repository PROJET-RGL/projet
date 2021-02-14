#include "perso.h"

perso_t init_perso(perso_t perso)
{
    // Coordonnées du personnage

    perso.perso.x = (FEN_LARGEUR - PERSO_LARGEUR) / 2 - 20;
    perso.perso.y = (FEN_HAUTEUR - PERSO_HAUTEUR) / 2 - 20;

    perso.perso.w = PERSO_LARGEUR;
    perso.perso.h = PERSO_HAUTEUR;

    // Génération des pv du personnage

    perso.pv = 10;

    // Emplacement du personnage dans le lab

    perso.tag = 0;

    // Création de la fenètre inv

    perso.inv.x = (FEN_LARGEUR - 200) / 2;
    perso.inv.y = (FEN_HAUTEUR - 100) / 2;

    perso.inv.w = 200;
    perso.inv.h = 100;

    return perso;
}
