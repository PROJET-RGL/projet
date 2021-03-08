#include "actualisation.h"

/**
 * \brief Fonction d'actualisation des salles du programme
 * \file 'actualisation.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.1
 * \date 18 Février 2020
 */

/**
 * @brief Gestion de l'actualisation d'une salle, de l'apparence de la texture
 * 
 * @param lab Positionnement du personnage en fonction de la salle actuelle
 * @param perso Les caractéristiques du personnage (couleur,vitesse,coordonnées)
 * @param renderer Attributs pour l'affichage d'une fenêtre
 * @param fenetre On importe la fenêtre modifiable
 * @return perso_t - Actualisation du personnage
 */

perso_t actualisation_salle(labyrinthe_t lab, perso_t perso, SDL_Renderer *renderer, SDL_Rect fenetre)
{
    nettoyage_ecran(renderer);

    // Affichage de la map

    if(SDL_RenderCopy(renderer, lab.texture, NULL, &fenetre) != 0)
    {
        clean_ressources(NULL, renderer, lab.texture);
        SDL_ExitWithError("Impossible d'afficher la texture !\n");
    }

    /*              DEBUG DE LA HITBOX DU SOL

    if(affichage(renderer, lab.tab_salle[perso.tag].salle , 255, 0, 0) != 1)
    {
        SDL_ExitWithError("Affichage salle raté");
    }

    */

    // Affichage des objets

    /*

    int i = 0;

    for(i = 0; i < lab.tab_salle[perso.tag].nb_objt; i++)
    {
                  DEBUG DE LA HITBOX OBJET

        affichage(renderer, lab.tab_salle[perso.tag].tab_obj[i].objet, 255, 0, 0);

        if(SDL_RenderCopy(renderer, lab.tab_salle[perso.tag].tab_obj[i].text_objet, NULL, &lab.tab_salle[perso.tag].tab_obj[i].objet) != 0)
        {
            clean_ressources(NULL, renderer, lab.tab_salle[perso.tag].tab_obj[i].text_objet);
            SDL_ExitWithError("Impossible d'afficher la texture !\n");
        }
    }

    */

    // Affichage des mobs

    int i = 0;

    for(i = 0; i < lab.tab_salle[perso.tag].nb_mob; i++)
    {
        /*              DEBUG DE LA HITBOX MOB

        affichage(renderer, lab.tab_salle[perso.tag].tab_mob[i].mob, 255, 0, 0);

        */


        if(lab.tab_salle[perso.tag].tab_mob[i].pv != 0)
        {
            if(SDL_RenderCopy(renderer, lab.tab_salle[perso.tag].tab_mob[i].texture, NULL, &lab.tab_salle[perso.tag].tab_mob[i].mob) != 0)
            {
                clean_ressources(NULL, renderer, lab.tab_salle[perso.tag].tab_mob[i].texture);
                SDL_ExitWithError("Impossible d'afficher la texture !\n");
            }
        }
    }

    perso = test_colision(perso, lab.tab_salle[perso.tag].salle);

    // Actualisation du personnage

    if(affichage(renderer, perso.perso, 255, 20, 20) != 1)
    {
        SDL_ExitWithError("Affichage perso raté");
    }

    // Affichage des portes

    if(affichage(renderer, lab.tab_salle[perso.tag].porte[0].porte, 67, 79, 226) != 1)
    {
        SDL_ExitWithError("Affichage porte raté");
    }

    if(perso.tag != 0)
    {
        if(affichage(renderer, lab.tab_salle[perso.tag].porte[1].porte, 67, 79, 226) != 1)
        {
            SDL_ExitWithError("Affichage porte raté");
        }
    }

    SDL_RenderPresent(renderer);
    return perso;
}
