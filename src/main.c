#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "salle.h"
#include "fonction_admin.h"
#include "perso.h"

// Fenêtre dimension

#define FEN_LARGEUR 1440
#define FEN_HAUTEUR 900

// Salle dimension

#define SALLE_LARGEUR (FEN_LARGEUR/10)*8
#define SALLE_HAUTEUR (FEN_HAUTEUR/10)*8

// Personnage Dimension

#define PERSO_LARGEUR 90
#define PERSO_HAUTEUR 90

// Stat perso

#define VITESSE 5

// Stat globale

#define DELAI 100

// Booleen

#define TRUE 1
#define FALSE 0

SDL_Window *fen = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;
SDL_Rect salle;
SDL_Rect perso;

// gcc src/main.c -o bin/main -I include src/salle.c src/fonction_admin.c src/perso.c -L lib -lmingw32 -lSDL2main -lSDL2

int main(int argc, char **argv)
{
    int touche1 = 0, touche2 = 0;

    if(creation_fen(&fen, &renderer, FEN_LARGEUR, FEN_HAUTEUR) != TRUE)
    {
        SDL_ExitWithError("Création du rendu raté, erreur 404 !");
    }

    nettoyage_ecran(renderer);

    salle = init_salle(renderer, salle, FEN_LARGEUR, FEN_HAUTEUR, SALLE_HAUTEUR, SALLE_LARGEUR);


    perso = init_perso(renderer, perso, FEN_LARGEUR, FEN_HAUTEUR, PERSO_HAUTEUR, PERSO_LARGEUR);

    SDL_bool program_lunched = TRUE;

    while(program_lunched != FALSE)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    program_lunched = FALSE;
                    break;

                case SDL_KEYDOWN :

                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            program_lunched = FALSE;
                            break;

                        case SDLK_q:
                            if(touche1 == 0)
                            {
                                touche1 = 'Q';
                            }
                            else if(touche2 == 0)
                            {
                                touche2 = 'Q';
                            }
                            break;

                        case SDLK_d:
                            if(touche1 == 0)
                            {
                                touche1 = 'D';
                            }
                            else if(touche2 == 0)
                            {
                                touche2 = 'D';
                            }
                            break;

                        case SDLK_s:
                            if(touche1 == 0)
                            {
                                touche1 = 'S';
                            }
                            else if(touche2 == 0)
                            {
                                touche2 = 'S';
                            }
                            break;

                        case SDLK_z:
                            if(touche1 == 0)
                            {
                                touche1 = 'Z';
                            }
                            else if(touche2 == 0)
                            {
                                touche2 = 'Z';
                            }
                            break;

                        default :
                            break;
                    }
                    SDL_Delay(DELAI);
                    perso = actualisation_perso(renderer, salle, perso, VITESSE + DELAI/2, touche1, touche2);
                    touche1 = 0;
                    touche2 = 0;

                default:
                    continue;
            }
        }

    }

    clean_ressources(fen, renderer, NULL);
    SDL_Quit();
}