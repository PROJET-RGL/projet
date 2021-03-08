#include "porte.h"

/**
 * \brief Fichier contenant les fonctions agissant sur les portes du programme
 * \file 'porte.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.1
 * \date 18 Février 2020
 */

/**
 * @brief Création d'une porte, avec ses coordonnées, sa taille, sa salle d'entrée et sa salle de sortie
 *
 * @param porte On importe la porte à modifié
 * @param x Coordonnées x de la porte
 * @param y Coordonnées y de la porte
 * @param salle_actuel identifiant de la salle d'entrée
 * @param salle_dest Identifiant de la salle de sortie
 * @param position Définit le sens de rotation de la porte
 * @return porte_t - Retourne la porte mis en paramètre
 */

porte_t init_porte(porte_t porte, int x, int y, int salle_actuel, int salle_dest, int position)
{
    if(position == 'V')
    {
        porte.porte.w = 20;
        porte.porte.h = 150;
    }else if(position == 'H')
    {
        porte.porte.w = 150;
        porte.porte.h = 20;
    }

    porte.porte.x = x;
    porte.porte.y = y - (porte.porte.h/2);

    porte.salle_entree = salle_actuel;
    porte.salle_dest = salle_dest;
    porte.position = position;

    return porte;
}

/**
 * @brief On test si le personnage rentre en collision avec la porte
 * 
 * @param perso On importe le personnage en question
 * @param porte On importe la porte en question
 * @param salle_actuel Salle dans laquel le personnage se situe
 * @param salle_dest Salle dans lequel le personnage doit aller si il y a collision
 * @return Salle_(actuel / dest) - Return la salle en fonction de si il y a collision ou pas
 */

int collision_porte(perso_t perso, porte_t porte, int salle_actuel, int salle_dest)
{
    /*
        Si perso.x + perso.w > porte.x && perso.x < salleorte.x + porte.w && perso.y + perso.h < porte.y && perso.y < porte.y + porte.h
        Alors on est dans le rectangle donc on change le tag de la salle du personnage
    */

    if((perso.perso.x + perso.perso.w) > porte.porte.x && (perso.perso.x) < (porte.porte.x + porte.porte.w) && (perso.perso.y + perso.perso.h) > porte.porte.y && (perso.perso.y) < (porte.porte.y + porte.porte.h))
    {    // on change de salle qui est entrée en paramètre
        return salle_dest;
    }else return salle_actuel;
}

