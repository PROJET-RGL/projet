#ifndef texture_H
#define texture_H

#include "super.h"
#include "fonction_admin.h"

SDL_Texture *init_texture(SDL_Renderer *renderer, SDL_Window *fen, char *chemin_image);
SDL_Rect afficher_texture(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *texture, SDL_Rect rect, SDL_bool plein_ecran, int pourcentX, int pourcentY);

void charger_textures_menu(SDL_Renderer *renderer, SDL_Window *fen, SDL_bool en_jeu, SDL_Texture *texture[7]);
void charger_textures_options(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *texture[10]);
void charger_textures_commandes(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *texture[8]);

#endif