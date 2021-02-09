#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"
#include "structure.h"
#include "actualisation.h"
#include "porte.h"

#define VITESSE 10

perso_t actualisation_salle(labyrinthe_t lab, perso_t perso, SDL_Renderer *renderer, int touche1, int touche2)
{
    nettoyage_ecran(renderer);

    // Affichage de la map

    if(affichage(renderer, lab.tab_salle[perso.tag].salle , lab.tab_salle[perso.tag].couleur.r, lab.tab_salle[perso.tag].couleur.v, lab.tab_salle[perso.tag].couleur.b) != 1)
    {
        SDL_ExitWithError("Affichage salle raté");
    }

    // Affichage des objets

    int i = 0;

    for(i = 0; i < N; i++)
    {
        affichage(renderer, lab.tab_salle[perso.tag].tab_obj[i].objet, lab.tab_salle[perso.tag].tab_obj[i].couleur.r, lab.tab_salle[perso.tag].tab_obj[i].couleur.v, lab.tab_salle[perso.tag].tab_obj[i].couleur.b);
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

    switch(test_colision(perso.perso, lab.tab_salle[perso.tag].salle, touche1, touche2, VITESSE))
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
