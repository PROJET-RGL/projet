#ifndef objet_H
#define objet_H

#include "super.h"
#include "fonction_admin.h"

objet_t init_obj(objet_t obj, SDL_Window *fen, SDL_Renderer *renderer, SDL_Surface *image);

objet_t compare_objet(objet_t obj1, objet_t obj2);

#endif