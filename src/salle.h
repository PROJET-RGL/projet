#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

int creation_fen(SDL_Window **fen, SDL_Renderer **renderer, int FEN_LARGEUR, int FEN_HAUTEUR);

SDL_Rect init_salle(SDL_Rect salle, int FEN_LARGEUR, int FEN_HAUTEUR, int SALLE_HAUTEUR, int SALLE_LARGEUR);

int test_colision(SDL_Rect perso, SDL_Rect salle, int touche1, int touche2, int VITESSE);

int collision_porte(SDL_Rect perso, SDL_Rect porte, int salle_actuel, int salle_dest, int VITESSE);

SDL_Rect init_porte(SDL_Rect porte, int x, int y, int position);