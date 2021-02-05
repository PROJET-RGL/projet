#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>


void SDL_ExitWithError(const char *message);

void clean_ressources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

void nettoyage_ecran(SDL_Renderer *renderer);

int affichage(SDL_Renderer *renderer, SDL_Rect cible, int r, int v, int b);