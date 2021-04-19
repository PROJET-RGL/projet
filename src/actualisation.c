#include "actualisation.h"

/**
 * \brief Fonction d'actualisation des salles du programme
 * \file 'actualisation.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief Gestion de l'actualisation d'une salle, de l'apparence de la texture
 * 
 * @param (*jeu) Importation de la partie actuel et Positionnement du personnage en fonction de la salle actuelle
 * @param renderer Attributs pour l'affichage d'une fenêtre
 * @param fenetre On importe la fenêtre modifiable
 * @return perso_t - Actualisation du personnage
 */

jeu_t actualisation_salle(jeu_t *jeu, SDL_Renderer *renderer, SDL_Rect fenetre, SDL_Window *fen)
{
    nettoyage_ecran(renderer);

    // Affichage de la map

    if(SDL_RenderCopy(renderer, (*jeu).lab.texture, NULL, &fenetre) != 0)
    {
        clean_ressources(NULL, renderer, (*jeu).lab.texture);
        SDL_ExitWithError("Impossible d'afficher la texture !\n");
    }

    //              DEBUG DE LA HITBOX DU SOL

    DEBUG_MODE{
        if(affichage(renderer, (*jeu).lab.tab_salle[(*jeu).perso.tag].salle , 255, 0, 0) != 1)
        {
            SDL_ExitWithError("Affichage salle raté");
        }
    }


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

    for(i = 0; i < (*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob; i++)
    {
        (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob = deplacement_mob((*jeu).perso.perso, (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob, i);
        //           DEBUG DE LA HITBOX MOB
        DEBUG_MODE
            affichage(renderer, (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob, 255, 0, 0);

        if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].pv <= 0)
        {
            (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].pv = 0;
        }


        if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].pv != 0)
        {
            if(SDL_RenderCopy(renderer, (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].texture, NULL, &(*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob) != 0)
            {
                clean_ressources(NULL, renderer, (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].texture);
                SDL_ExitWithError("Impossible d'afficher la texture !\n");
            }
        }
    }

    (*jeu).perso = test_colision((*jeu).perso, (*jeu).lab.tab_salle[(*jeu).perso.tag].salle);

    // Actualisation du personnage

    if(jeu->perso.arme_actuelle == 0)
    {
        afficher_texture(renderer, fen, jeu->perso.textures_perso[0], jeu->perso.perso, 0, -1, -1, jeu->perso.perso.x, jeu->perso.perso.y);
    }


    if(jeu->perso.arme_actuelle == 1)
    {
        afficher_texture(renderer, fen, jeu->perso.textures_perso[1], jeu->perso.perso, 0, -1, -1, jeu->perso.perso.x, jeu->perso.perso.y);
    }


    // Affichage des portes

    DEBUG_MODE
    {
        if(affichage(renderer, (*jeu).lab.tab_salle[(*jeu).perso.tag].porte[0].porte, 67, 79, 226) != 1)
        {
            SDL_ExitWithError("Affichage porte raté");
        }

        if((*jeu).perso.tag != 0)
        {
            if(affichage(renderer, (*jeu).lab.tab_salle[(*jeu).perso.tag].porte[1].porte, 67, 79, 226) != 1)
            {
                SDL_ExitWithError("Affichage porte raté");
            }
        }
    }

    return (*jeu);
}
