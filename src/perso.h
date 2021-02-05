#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#define N 3

SDL_Rect init_perso(SDL_Rect perso, int FEN_LARGEUR, int FEN_HAUTEUR, int PERSO_HAUTEUR, int PERSO_LARGEUR);

SDL_Rect actualisation_perso(SDL_Renderer *renderer, SDL_Rect salle, SDL_Rect porte, SDL_Rect perso, SDL_Rect tab_obj[N], int VITESSE, int touche1, int touche2, int r, int v, int b);