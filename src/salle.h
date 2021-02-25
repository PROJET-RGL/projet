#ifndef salle_H
#define salle_H

#include "super.h"
#include "mob.h"
#include "objet.h"
#include "porte.h"
#include "fonction_admin.h"

int creation_fen(SDL_Window **fen, SDL_Renderer **renderer);

salle_t init_salle(salle_t salle, SDL_Window *fen, SDL_Renderer *renderer, int tag);

perso_t test_colision(perso_t perso, SDL_Rect salle);

#endif