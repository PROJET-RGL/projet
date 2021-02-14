#ifndef menu_H
#define menu_H

#include "super.h"
#include "fonction_admin.h"
//#include "option.h"

SDL_Rect logo;
SDL_Rect start;
SDL_Rect option;
SDL_Rect quit;

int load_menu(SDL_Renderer *renderer, SDL_Window *fen);
SDL_Rect load_img(SDL_Renderer *renderer, SDL_Window *fen, char *img, int pourcentX, int pourcentY, SDL_Rect rect);



SDL_Rect fleche;
SDL_Rect fullscreen;
SDL_Rect classique;

int load_option(SDL_Renderer *renderer, SDL_Window *fen);

#endif