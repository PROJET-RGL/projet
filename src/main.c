#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "salle.h"
#include "fonction_admin.h"
#include "perso.h"
#include "objet.h"
#include "porte.h"
#include "labyrinthe.h"
#include "structure.h"
#include "actualisation.h"
#include "mob.h"

//

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
#define TAILLE_LAB 7

// Booleen

#define TRUE 1
#define FALSE 0

SDL_Window *fen = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;
labyrinthe_t lab;
perso_t perso1;
objet_t objet1;
int perso_salle, passage;

int main(int argc, char **argv)
{
    int touche1 = 0, touche2 = 0;

    perso_salle = 1;

    if(creation_fen(&fen, &renderer, FEN_LARGEUR, FEN_HAUTEUR) != TRUE)
    {
        SDL_ExitWithError("Création du rendu raté, erreur 404 !");
    }

    nettoyage_ecran(renderer);

    // Création lab

    srand(time(NULL));

    lab = init_lab(lab, TAILLE_LAB, FEN_LARGEUR, FEN_HAUTEUR, SALLE_HAUTEUR, SALLE_LARGEUR);

    // Création personnage !

    perso1 = init_perso(perso1, FEN_LARGEUR, FEN_HAUTEUR, PERSO_HAUTEUR, PERSO_LARGEUR);

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


            if(perso1.tag == 0)
            {
                printf("Salle une !\n");
                perso1 = actualisation_salle(lab, perso1, renderer, 0, 255, 0, touche1, touche2);
                // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                if(collision_porte(perso1, lab.tab_salle[perso1.tag].porte[0], lab.tab_salle[perso1.tag].porte[0].salle_entree, lab.tab_salle[perso1.tag].porte[0].salle_dest, VITESSE) != 0)
                {
                    perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y + lab.tab_salle[perso1.tag].salle.h ) - (lab.tab_salle[perso1.tag].porte[1].porte.h)/2 - perso1.perso.h - 100;
                    perso1.tag++;
                }
                SDL_Delay(20);
                break;
            }else if(perso1.tag > 0 && perso1.tag < 7){
                printf("Salle suivante !\n");
                perso1 = actualisation_salle(lab, perso1, renderer, 0, 0, 255, touche1, touche2);
                // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                if(collision_porte(perso1, lab.tab_salle[perso1.tag].porte[0], lab.tab_salle[perso1.tag].porte[0].salle_entree, lab.tab_salle[perso1.tag].porte[0].salle_dest, VITESSE) != 0)
                {
                    perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y + lab.tab_salle[perso1.tag].salle.h ) - (lab.tab_salle[perso1.tag].porte[0].porte.h)/2 - perso1.perso.h;
                    perso1.tag++;

                }else if(collision_porte(perso1, lab.tab_salle[perso1.tag].porte[1], lab.tab_salle[perso1.tag].porte[1].salle_entree, lab.tab_salle[perso1.tag].porte[1].salle_dest, VITESSE) != 0)
                {   // Si on touche la porte du bas, on passe à la salle précédente et on spawn en haut
                    perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y) + (lab.tab_salle[perso1.tag].porte[1].porte.h)/2;
                    perso1.tag--;
                }
                SDL_Delay(20);
                break;
            }
        }
    }
    clean_ressources(fen, renderer, NULL);
    SDL_Quit();
}