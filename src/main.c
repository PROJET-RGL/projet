#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "salle.h"
#include "fonction_admin.h"
#include "perso.h"
#include "objet.h"

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
SDL_Rect salle1;
SDL_Rect salle2;
SDL_Rect perso;
SDL_Rect porte1;
SDL_Rect porte2;
SDL_Rect tab_obj[N] = {0};
int perso_salle, passage;

// gcc src/main.c -o bin/main -I include src/salle.c src/fonction_admin.c src/perso.c src/objet.c -L lib -lmingw32 -lSDL2main -lSDL2

int main(int argc, char **argv)
{
    int touche1 = 0, touche2 = 0;

    perso_salle = 1;

    if(creation_fen(&fen, &renderer, FEN_LARGEUR, FEN_HAUTEUR) != TRUE)
    {
        SDL_ExitWithError("Création du rendu raté, erreur 404 !");
    }

    nettoyage_ecran(renderer);

    // Création des salles aléatoirement !

    salle1 = init_salle(salle1, FEN_LARGEUR, FEN_HAUTEUR, SALLE_HAUTEUR, SALLE_LARGEUR);

    salle2 = init_salle(salle2, FEN_LARGEUR, FEN_HAUTEUR, SALLE_HAUTEUR, SALLE_LARGEUR);

    // Création personnage !

    perso = init_perso(perso, FEN_LARGEUR, FEN_HAUTEUR, PERSO_HAUTEUR, PERSO_LARGEUR);

    // Création porte !

    porte1 = init_porte(porte1, (salle1.x + salle1.w)/2, salle1.y, 'H');
    porte2 = init_porte(porte2, (salle2.x + salle2.w)/2, (salle2.y + salle2.h), 'H');

    // Création des objets

    int i = 0;

    srand(time(NULL));

    for(i = 0; i < N; i++)
    {
        tab_obj[i] = init_obj(tab_obj[i]);
    }


    // Boucle de jeu !

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

                case SDL_KEYUP :

                    switch(event.key.keysym.sym)
                    {
                        case SDLK_q:
                            if(touche1 == 'Q')
                            {
                                touche1 = 0;
                            }
                            if(touche2 == 'Q')
                            {
                                touche2 = 0;
                            }
                            continue;

                        case SDLK_d:
                            if(touche1 == 'D')
                            {
                                touche1 = 0;
                            }
                            if(touche2 == 'D')
                            {
                                touche2 = 0;
                            }
                            continue;

                        case SDLK_s:
                            if(touche1 == 'S')
                            {
                                touche1 = 0;
                            }
                            if(touche2 == 'S')
                            {
                                touche2 = 0;
                            }
                            continue;

                        case SDLK_z:
                            if(touche1 == 'Z')
                            {
                                touche1 = 0;
                            }
                            if(touche2 == 'Z')
                            {
                                touche2 = 0;
                            }
                            continue;

                        default :
                            continue;
                    }
                    break;

                case SDL_KEYDOWN :

                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            program_lunched = FALSE;
                            break;

                        case SDLK_q:
                            if(touche1 == 0 && touche1 != 'Q')
                            {
                                touche1 = 'Q';
                            }
                            else if(touche2 == 0 && touche1 != 'Q')
                            {
                                touche2 = 'Q';
                            }
                            continue;

                        case SDLK_d:
                            if(touche1 == 0 && touche1 != 'D')
                            {
                                touche1 = 'D';
                            }
                            else if(touche2 == 0 && touche1 != 'D')
                            {
                                touche2 = 'D';
                            }
                            continue;

                        case SDLK_s:
                            if(touche1 == 0 && touche1 != 'S')
                            {
                                touche1 = 'S';
                            }
                            else if(touche2 == 0 && touche1 != 'S')
                            {
                                touche2 = 'S';
                            }
                            continue;

                        case SDLK_z:
                            if(touche1 == 0 && touche1 != 'Z')
                            {
                                touche1 = 'Z';
                            }
                            else if(touche2 == 0 && touche1 != 'Z')
                            {
                                touche2 = 'Z';
                            }
                            continue;

                        default :
                            continue;
                    }
                    break;

                default:
                    break;
            }
            if(perso_salle == 1){
                perso = actualisation_perso(renderer, salle1, porte1, perso, tab_obj, VITESSE * 2, touche1, touche2, 0, 255, 0);
                perso_salle = collision_porte(perso, porte1, 1, 2, VITESSE);
                if(perso_salle != 1)
                {
                    perso.y = (salle2.y + salle2.h ) - porte2.h/2 - perso.h;
                }
                SDL_Delay(20);
            }else if(perso_salle == 2){
                perso = actualisation_perso(renderer, salle2, porte2, perso, tab_obj, VITESSE * 2, touche1, touche2, 0, 0, 255);
                perso_salle = collision_porte(perso, porte2, 2, 1, VITESSE);
                if(perso_salle != 2)
                {
                    perso.y = salle1.y + porte1.h/2;
                }
                SDL_Delay(20);
            }

        }

    }

    clean_ressources(fen, renderer, NULL);
    SDL_Quit();
}