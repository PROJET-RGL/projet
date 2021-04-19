#include "perso.h"

/**
 * \brief Fichier contenant les fonctions agissant sur le personnage du programme
 * \file 'perso.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief Création du perso, avec ses coordonnées, sa taille, ses points de vies, son emplacement, son inventaire et sa vitesse
 * 
 * @param perso On importe le perso à modifier
 * @return perso_t - Retourne le perso mis en paramètre
 */

perso_t init_perso(jeu_t *jeu)
{
    arme_t arme;
    // Coordonnées du personnage

    (*jeu).perso.perso.x = (FEN_LARGEUR - PERSO_LARGEUR) / 2 - 20;
    (*jeu).perso.perso.y = (FEN_HAUTEUR - PERSO_HAUTEUR) / 2 - 20;

    (*jeu).perso.perso.w = PERSO_LARGEUR;
    (*jeu).perso.perso.h = PERSO_HAUTEUR;

    // Génération des pv du personnage

    (*jeu).perso.pv = 10;

    // Emplacement du personnage dans le lab

    (*jeu).perso.tag = 0;

    // Initialisation du vecteur vitesse

    (*jeu).perso.velocite.x = 0;
    (*jeu).perso.velocite.y = 0;

    // On incremente le nombre d'arme

    (*jeu).perso.nb_arme++;

    // On ajoute une arme

    (*jeu).perso.tab_arme[0] = new_arme(jeu, 0, "Pistolet", "le pistolet de base", 400, 5, 5, 10000, 0, 'D', 0, (*jeu).perso.inv.cases[9].pos_case);
    (*jeu).perso.tab_arme[1] = new_arme(jeu, 1, "Épée", "l'épée de base", 200, 6, 1, 0, 10000, 'C', 0, (*jeu).perso.inv.cases[10].pos_case);
    (*jeu).perso.inv.loot.potion[0] = new_potion(jeu, "Heal", 5, (*jeu).perso.inv.cases[0].pos_case, 10);
    // (*jeu).perso.inv.cases[0].est_vide = SDL_FAUX;
    (*jeu).perso.inv.loot.potion[0].nb_potion = 3;

    // Arme actuelle = tag arme

    (*jeu).perso.arme_actuelle = 0;

    // Initialisation de la quantité d'argent

    (*jeu).perso.argent = 0;

    // Initialisation du score

    (*jeu).perso.score = 0;

    return (*jeu).perso;
}
