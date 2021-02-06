#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"
#include "structure.h"

perso_t init_perso(perso_t perso, int FEN_LARGEUR, int FEN_HAUTEUR, int PERSO_HAUTEUR, int PERSO_LARGEUR)
{
    // Coordonnées du personnage

    perso.perso.x = (FEN_LARGEUR - PERSO_LARGEUR) / 2;
    perso.perso.y = (FEN_HAUTEUR - PERSO_HAUTEUR) / 2;

    perso.perso.w = PERSO_LARGEUR;
    perso.perso.h = PERSO_HAUTEUR;

    // Génération des pv du personnage

    perso.pv = 10;

    // Emplacement du personnage dans le lab

    perso.tag = 0;

    return perso;
}

SDL_Rect actualisation_perso(SDL_Renderer *renderer, SDL_Rect salle, SDL_Rect porte, SDL_Rect perso, SDL_Rect tab_obj[N], int VITESSE, int touche1, int touche2, int r, int v, int b)
{
    nettoyage_ecran(renderer);

    if(affichage(renderer, salle, r, v, b) != 1)
    {
        SDL_ExitWithError("Affichage salle raté");
    }

    int i =0;

    for(i = 0; i < N; i++)
    {
        affichage(renderer, tab_obj[i], 0, 255, 255);
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

    switch(test_colision(perso, salle, touche1, touche2, VITESSE))
    {
        case 1 :    // Gauche
            perso.x = perso.x - VITESSE;
            break;

        case 5 :    // Droite
            perso.x = perso.x + VITESSE;
            break;

        case 10 :   // Haut
            perso.y = perso.y - VITESSE;
            break;

        case 20 :   // Bas
            perso.y = perso.y + VITESSE;
            break;

        case 11 :   // Gauche - haut
            perso.x = perso.x - VITESSE;
            perso.y = perso.y - VITESSE;
            break;

        case 21 :   // Gauche - bas
            perso.x = perso.x - VITESSE;
            perso.y = perso.y + VITESSE;
            break;

        case 15 :   // Haut - droite
            perso.x = perso.x + VITESSE;
            perso.y = perso.y - VITESSE;
            break;

        case 25 :   // Bas - droite
            perso.x = perso.x + VITESSE;
            perso.y = perso.y + VITESSE;
            break;

        case 50 :   // On colle à gauche
            perso.x = salle.x + 1;
            break;

        case 51 :   // On colle à droite
            perso.x = (salle.x + salle.w) - perso.w - 1;
            break;

        case 52 :   // On colle en haut
            perso.y = salle.y + 1;
            break;

        case 53 :   // On colle en bas
            perso.y = (salle.y + salle.h) - perso.h - 1;
            break;

        default : break;
    }


    if(affichage(renderer, perso, 255, 20, 20) != 1)
    {
        SDL_ExitWithError("Affichage perso raté");
    }

    if(affichage(renderer, porte, 67, 79, 226) != 1)
    {
        SDL_ExitWithError("Affichage porte raté");
    }

    SDL_RenderPresent(renderer);
    return perso;
}
