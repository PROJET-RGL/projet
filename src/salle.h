#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

SDL_Rect clavierLecture(SDL_Window *fen, SDL_Renderer *rend, SDL_Event event, SDL_Texture *PersoText, SDL_Texture *Fond, SDL_Rect IMGFond, SDL_Rect fond, SDL_Rect bloc, SDL_Rect perso, int direction);

int creation_fen(SDL_Window **fen, SDL_Renderer **renderer, int FEN_LARGEUR, int FEN_HAUTEUR);

SDL_Rect init_salle(SDL_Renderer *renderer, SDL_Rect salle, int FEN_LARGEUR, int FEN_HAUTEUR, int SALLE_HAUTEUR, int SALLE_LARGEUR);

int test_colision(SDL_Rect perso, SDL_Rect salle, int touche1, int touche2, int VITESSE);