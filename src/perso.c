#include "perso.h"

/**
 * \brief Fichier contenant les fonctions agissant sur le personnage du programme
 * \file 'perso.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.1
 * \date 18 Février 2020
 */

/**
 * @brief Création du perso, avec ses coordonnées, sa taille, ses points de vies, son emplacement, son inventaire et sa vitesse
 * 
 * @param perso On importe le perso à modifier
 * @return perso_t - Retourne le perso mis en paramètre
 */

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

    // Initialisation du vecteur vitesse

    perso.velocite.x = 0;
    perso.velocite.y = 0;

    return perso;
}
