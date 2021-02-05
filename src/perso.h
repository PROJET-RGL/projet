#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

SDL_Rect init_perso(SDL_Renderer *renderer, SDL_Rect perso, int FEN_LARGEUR, int FEN_HAUTEUR, int PERSO_HAUTEUR, int PERSO_LARGEUR);

SDL_Rect actualisation_perso(SDL_Renderer *renderer, SDL_Rect salle, SDL_Rect perso, int VITESSE, int touche1, int touche2);