#ifndef fonction_admin_H
#define fonction_admin_H

#include "super.h"

void SDL_ExitWithError(const char *message);

void clean_ressources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

void nettoyage_ecran(SDL_Renderer *renderer);

int affichage(SDL_Renderer *renderer, SDL_Rect cible, int r, int v, int b);

#endif