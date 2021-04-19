#ifndef mob_H
#define mob_H

#include "fonction_admin.h"

mob_t init_mob(mob_t mob, SDL_Window *fen, SDL_Renderer *renderer, SDL_Surface *image, int taille);

int colision_mob(mob_t mob1, perso_t perso);

mob_t compare_mob(mob_t mob1, mob_t mob2);

SDL_Rect deplacement_mob(SDL_Rect perso, SDL_Rect mob, int i);

#endif