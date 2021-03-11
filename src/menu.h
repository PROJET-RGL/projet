#ifndef menu_H
#define menu_H

#include "super.h"
#include "fonction_admin.h"
#include "sauvegarde.h"

SDL_Rect logo;
SDL_Rect start;
SDL_Rect option;
SDL_Rect quit;
SDL_Rect nouvelle;
SDL_Rect charger;

int load_menu(SDL_Renderer *renderer, SDL_Window *fen, int *volume, SDL_bool *plein_ecran, SDL_bool ingame, SDL_bool *charge, jeu_t *jeu);
SDL_Rect load_img(SDL_Renderer *renderer, SDL_Window *fen, char *img, int pourcentX, int pourcentY, SDL_Rect rect, SDL_bool *plein_ecran);
void reload_img(SDL_Renderer *renderer, SDL_Window *fen, int *volume, SDL_bool *plein_ecran, int choix);

SDL_Rect haut;
SDL_Rect bas;
SDL_Rect gauche;
SDL_Rect droite;
SDL_Rect z;
SDL_Rect q;
SDL_Rect s;
SDL_Rect d;

SDL_Rect general;
SDL_Rect commandes;
SDL_Rect retour;
SDL_Rect fullscreen;
SDL_Rect classique;
SDL_Rect son;
SDL_Rect son_down;
SDL_Rect son_up;
SDL_Rect son_barreup;
SDL_Rect son_barredown;

void load_option(SDL_Renderer *renderer, SDL_Window *fen, int *volume, SDL_bool *plein_ecran);

#endif