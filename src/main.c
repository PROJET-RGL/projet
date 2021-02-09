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

// gcc src/main.c -o bin/main -I include src/salle.c src/fonction_admin.c src/perso.c src/objet.c src/porte.c src/structure.c src/labyrinthe.c src/actualisation.c src/mob.c -L lib -lmingw32 -lSDL2main -lSDL2

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
labyrinthe_t lab;
perso_t perso1;
objet_t objet1;
SDL_Rect fenetre;
SDL_Surface *image = NULL;

int perso_salle, passage;

int main(int argc, char **argv)
{
    int touche1 = 0, touche2 = 0;

    perso_salle = 1;

    if(creation_fen(&fen, &renderer, FEN_LARGEUR, FEN_HAUTEUR) != TRUE)
    {
        SDL_ExitWithError("Création du rendu raté, erreur 404 !");
    }

    // Rectangle de la fenetre

    fenetre.x = 0;
    fenetre.y = 0;

    fenetre.h = FEN_HAUTEUR;
    fenetre.w = FEN_LARGEUR;

    nettoyage_ecran(renderer);

    // Création lab

    srand(time(NULL));

    lab = init_lab(lab, TAILLE_LAB + 1, FEN_LARGEUR, FEN_HAUTEUR, SALLE_HAUTEUR, SALLE_LARGEUR);

    // Création personnage !

    perso1 = init_perso(perso1, FEN_LARGEUR, FEN_HAUTEUR, PERSO_HAUTEUR, PERSO_LARGEUR);

    // Initialisation de la texture des salles !!!



    image = SDL_LoadBMP("src/Salle.BMP");               // <---- " ", c

    if(image == NULL)
    {
        clean_ressources(fen, renderer, NULL);
        SDL_ExitWithError("Erreur du chargement de l'image");
    }

    int i = 0;

        lab.texture = SDL_CreateTextureFromSurface(renderer, image);

        if(lab.texture == NULL)
        {
            clean_ressources(fen, renderer, lab.texture);
            SDL_ExitWithError("Erreur de création de la texture");
        }

        if(SDL_QueryTexture(lab.texture, NULL, NULL, &fenetre.w, &fenetre.h) != 0)
        {
            clean_ressources(fen, renderer, lab.texture);
            SDL_ExitWithError("Erreur de chargement de la texture");
        }

    SDL_FreeSurface(image);

    if(SDL_RenderCopy(renderer, lab.texture, NULL, &fenetre) != 0)
    {
        clean_ressources(fen, renderer, lab.texture);
        SDL_ExitWithError("Impossible d'afficher la texture !\n");
    }

    printf("C'est coller !");
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

    // ---------------------------------------------------------------------------------

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
                printf("Salle %d !\n", perso1.tag);
                perso1 = actualisation_salle(lab, perso1, renderer, touche1, touche2);
                // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                if(collision_porte(perso1, lab.tab_salle[perso1.tag].porte[0], lab.tab_salle[perso1.tag].porte[0].salle_entree, lab.tab_salle[perso1.tag].porte[0].salle_dest, VITESSE) != lab.tab_salle[perso1.tag].tag_salle)
                {
                    perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y + lab.tab_salle[perso1.tag].salle.h ) - (lab.tab_salle[perso1.tag].porte[0].porte.h)/2 - perso1.perso.h - 100;
                    perso1.tag = lab.tab_salle[perso1.tag].tag_salle + 1;
                }
                SDL_Delay(20);
                break;
            }else if(perso1.tag < TAILLE_LAB - 1 && perso1.tag > 0){
                printf("Salle %d !\n", perso1.tag);
                perso1 = actualisation_salle(lab, perso1, renderer, touche1, touche2);
                // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                if(collision_porte(perso1, lab.tab_salle[perso1.tag].porte[1], lab.tab_salle[perso1.tag].porte[1].salle_entree, lab.tab_salle[perso1.tag].porte[1].salle_dest, VITESSE) != lab.tab_salle[perso1.tag].tag_salle)
                {
                    printf("Porte du haut touché !\n");
                    perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y + lab.tab_salle[perso1.tag].salle.h ) - (lab.tab_salle[perso1.tag].porte[1].porte.h)/2 - perso1.perso.h;
                    if(perso1.tag < 6)
                        perso1.tag = lab.tab_salle[perso1.tag].tag_salle + 1;

                }else if(collision_porte(perso1, lab.tab_salle[perso1.tag].porte[0], lab.tab_salle[perso1.tag].porte[0].salle_entree, lab.tab_salle[perso1.tag].porte[0].salle_dest, VITESSE) != lab.tab_salle[perso1.tag].tag_salle)
                {   // Si on touche la porte du bas, on passe à la salle précédente et on spawn en haut
                    printf("Porte du bas touché !\n");
                    perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y) + (lab.tab_salle[perso1.tag].porte[0].porte.h)/2;
                    perso1.tag = lab.tab_salle[perso1.tag].tag_salle - 1;
                }
                SDL_Delay(20);
                break;
            }else if(perso1.tag == TAILLE_LAB - 1)
            {
                printf("Salle %d !\n", perso1.tag);
                perso1 = actualisation_salle(lab, perso1, renderer, touche1, touche2);
                // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                if(collision_porte(perso1, lab.tab_salle[perso1.tag].porte[1], lab.tab_salle[perso1.tag].porte[1].salle_entree, lab.tab_salle[perso1.tag].porte[1].salle_dest, VITESSE) != lab.tab_salle[perso1.tag].tag_salle)
                {
                    perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y) + (lab.tab_salle[perso1.tag].porte[1].porte.h)/2;
                    perso1.tag = lab.tab_salle[perso1.tag].tag_salle - 1;
                }
                SDL_Delay(20);
                break;
            }
        }
    }
    clean_ressources(fen, renderer, NULL);
    SDL_Quit();
}