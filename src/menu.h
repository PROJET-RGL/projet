#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Rect logo;
SDL_Rect start;
SDL_Rect option;
SDL_Rect quit;

int load_menu(SDL_Renderer *renderer, SDL_Window *fen, int FEN_LARGEUR, int FEN_HAUTEUR);
SDL_Rect load_img(SDL_Renderer *renderer, SDL_Window *fen, int FEN_LARGEUR, int FEN_HAUTEUR, char *img, int pourcentX, int pourcentY, SDL_Rect rect);