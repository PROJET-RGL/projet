#ifndef menu_H
#define menu_H

#include "super.h"
#include "fonction_admin.h"
#include "sauvegarde.h"
#include "texture.h"

SDL_Rect pos_menu[7];
SDL_Rect pos_options[10];
SDL_Rect pos_commandes[8];

SDL_bool load_menu(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *menu[7], SDL_Texture *options[10], SDL_Texture *commandes[10], int *volume, SDL_bool *charge, jeu_t *jeu, SDL_bool *plein_ecran, SDL_bool *program_launched, SDL_bool en_partie);
SDL_bool load_option(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *options[10], SDL_Texture *commandes[10], int *volume, SDL_bool *plein_ecran);

void reload_img(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *menu[7], SDL_Texture *options[10], SDL_Texture *commandes[10], int *volume, SDL_bool plein_ecran, int choix);

#endif