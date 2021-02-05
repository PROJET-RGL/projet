#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"

SDL_Rect init_perso(SDL_Renderer *renderer, SDL_Rect perso, int FEN_LARGEUR, int FEN_HAUTEUR, int PERSO_HAUTEUR, int PERSO_LARGEUR)
{
    perso.x = (FEN_LARGEUR - PERSO_LARGEUR) / 2;
    perso.y = (FEN_HAUTEUR - PERSO_HAUTEUR) / 2;

    perso.w = PERSO_LARGEUR;
    perso.h = PERSO_HAUTEUR;


    if(affichage(renderer, perso, 255, 20, 20) != 1)
    {
        SDL_ExitWithError("Affichage perso raté");
    }

    SDL_RenderPresent(renderer);
    return perso;
}

SDL_Rect actualisation_perso(SDL_Renderer *renderer, SDL_Rect salle, SDL_Rect perso, int VITESSE, int touche1, int touche2)
{
    nettoyage_ecran(renderer);

    if(affichage(renderer, salle, 180, 155, 146) != 1)
    {
        SDL_ExitWithError("Affichage salle raté");
    }


    switch(test_colision(perso, salle, touche1, touche2, VITESSE))
    {
        case 0 :
            break;

        case 1 :
            perso.x = perso.x - VITESSE;
            break;

        case 2 :
            perso.x = perso.x + VITESSE;
            break;

        case 3 :
            perso.y = perso.y - VITESSE;
            break;

        case 4 :
            perso.y = perso.y + VITESSE;
            break;

        default : break;
    }


    if(affichage(renderer, perso, 255, 20, 20) != 1)
    {
        SDL_ExitWithError("Affichage perso raté");
    }

    SDL_RenderPresent(renderer);
    return perso;
}
