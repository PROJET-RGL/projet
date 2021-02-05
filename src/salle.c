#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>


#include "salle.h"
#include "fonction_admin.h"


int creation_fen(SDL_Window **fen, SDL_Renderer **renderer, int FEN_LARGEUR, int FEN_HAUTEUR)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("Erreur du chargement du SDL");
    }

    if(SDL_CreateWindowAndRenderer(FEN_LARGEUR, FEN_HAUTEUR, 0, fen, renderer) != 0)
    {
        SDL_ExitWithError("Erreur de création de la fenêtre + le rendu");
    }

    return 1;
}

SDL_Rect init_salle(SDL_Renderer *renderer, SDL_Rect salle, int FEN_LARGEUR, int FEN_HAUTEUR, int SALLE_HAUTEUR, int SALLE_LARGEUR)
{

    salle.x = (FEN_LARGEUR - SALLE_LARGEUR)/2;
    salle.y = (FEN_HAUTEUR - SALLE_HAUTEUR)/2;

    salle.w = SALLE_LARGEUR;
    salle.h = SALLE_HAUTEUR;

    if(affichage(renderer, salle, 180, 155, 146) != 1)
    {
        SDL_ExitWithError("Affichage salle raté");
    }

    SDL_RenderPresent(renderer);
    return salle;
}

int test_colision(SDL_Rect perso, SDL_Rect salle, int touche1, int touche2, int VITESSE)
{
    SDL_Rect persoGHOST;
    int sortie = 0;

    persoGHOST.x = perso.x;
    persoGHOST.y = perso.y;

    persoGHOST.w = perso.w;
    persoGHOST.h = perso.h;

    if(touche1 == 'Q' || touche2 == 'Q')
    {
        persoGHOST.x = perso.x - VITESSE;
        if(persoGHOST.x < salle.x)
        {
            // Nous sommes en dehors, donc c'est pas bon
            sortie = 50;    // Message d'erreur lié au passage de bordure par la gauche
        }else sortie += 1;  // on return 1 car c'est possible de ce déplacer
    }
    if(touche1 == 'D' || touche2 == 'D')
    {
        persoGHOST.x = perso.x + VITESSE;
        if(persoGHOST.x + perso.w > salle.x + salle.w)
        {
            // Nous sommes en dehors, donc c'est pas bon
            sortie = 51;    // Message d'erreur lié au passage de bordure par la droite
        }else sortie += 5;  // on return 1 car c'est possible de ce déplacer
    }
    if(touche1 == 'Z' || touche2 == 'Z')
    {
        persoGHOST.y = perso.y - VITESSE;
        if(persoGHOST.y < salle.y)
        {
            // Nous sommes en dehors, donc c'est pas bon
            sortie = 52;    // Message d'erreur lié au passage de bordure par le haut
        }else sortie += 10; // on return 1 car c'est possible de ce déplacer
    }
    if(touche1 == 'S' || touche2 == 'S')
    {
        persoGHOST.y = perso.y + VITESSE;
        if(persoGHOST.y + perso.h > salle.y + salle.h)
        {
            // Nous sommes en dehors par le bas, donc c'est pas bon
            sortie = 53;    // Message d'erreur lié au passage de bordure par le bas
        }else sortie += 20; // on ajoute 20 à sortie car c'est possible de ce déplacer
    }

    return sortie;
}