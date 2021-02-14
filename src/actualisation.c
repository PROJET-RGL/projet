#include "actualisation.h"

perso_t actualisation_salle(labyrinthe_t lab, perso_t perso, SDL_Renderer *renderer, SDL_Rect fenetre, int touche1, int touche2)
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
        /*          DEBUG DE LA HITBOX MOB

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

    /*
        G = 1                   // on se déplace vers le gauche
        D = 5                   // on se déplace vers la droite
        H = 10                  // on se déplace vers le haut
        B = 20                  // on se déplace vers le bas
        G + D = 1 + 5 = 6       // On annule le mouvement
        G + H = 1 + 10 = 11     // On se déplace en diagonale gauche/haut
        G + B = 1 + 20 = 21     // On se déplace en diagonale gauche/bas
        D + H = 5 + 10 = 15     // On se déplace en diagonale droite/haut
        D + B = 5 + 20 = 25     // on se dépalce en diagonale droite/bas
        H + B = 10 + 20 = 30    // On annule le mouvement
    */

    switch(test_colision(perso.perso, lab.tab_salle[perso.tag].salle, touche1, touche2))
    {
        case 1 :    // Gauche
            perso.perso.x = perso.perso.x - VITESSE;
            break;

        case 5 :    // Droite
            perso.perso.x = perso.perso.x + VITESSE;
            break;

        case 10 :   // Haut
            perso.perso.y = perso.perso.y - VITESSE;
            break;

        case 20 :   // Bas
            perso.perso.y = perso.perso.y + VITESSE;
            break;

        case 11 :   // Gauche - haut
            perso.perso.x = perso.perso.x - VITESSE;
            perso.perso.y = perso.perso.y - VITESSE;
            break;

        case 21 :   // Gauche - bas
            perso.perso.x = perso.perso.x - VITESSE;
            perso.perso.y = perso.perso.y + VITESSE;
            break;

        case 15 :   // Haut - droite
            perso.perso.x = perso.perso.x + VITESSE;
            perso.perso.y = perso.perso.y - VITESSE;
            break;

        case 25 :   // Bas - droite
            perso.perso.x = perso.perso.x + VITESSE;
            perso.perso.y = perso.perso.y + VITESSE;
            break;

        case 50 :   // On colle à gauche
            perso.perso.x = lab.tab_salle[perso.tag].salle.x + 1;
            break;

        case 51 :   // On colle à droite
            perso.perso.x = (lab.tab_salle[perso.tag].salle.x + lab.tab_salle[perso.tag].salle.w) - perso.perso.w - 1;
            break;

        case 52 :   // On colle en haut
            perso.perso.y = lab.tab_salle[perso.tag].salle.y + 1;
            break;

        case 53 :   // On colle en bas
            perso.perso.y = (lab.tab_salle[perso.tag].salle.y + lab.tab_salle[perso.tag].salle.h) - perso.perso.h - 1;
            break;

        default : break;
    }

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
