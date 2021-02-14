#ifndef salle_H
#define salle_H

#include "super.h"
#include "mob.h"
#include "objet.h"
#include "porte.h"
#include "fonction_admin.h"

int creation_fen(SDL_Window **fen, SDL_Renderer **renderer);

salle_t init_salle(salle_t salle, int tag);

int test_colision(SDL_Rect perso, SDL_Rect salle, int touche1, int touche2);

#endif