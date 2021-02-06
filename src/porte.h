#ifndef porte_H
#define porte_H

#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "salle.h"
#include "fonction_admin.h"
#include "perso.h"
#include "objet.h"
#include "labyrinthe.h"
#include "structure.h"
#include "actualisation.h"

int collision_porte(perso_t perso, porte_t porte, int salle_actuel, int salle_dest, int VITESSE);

porte_t init_porte(porte_t porte, int x, int y, int salle_actuel, int salle_dest, int position);

#endif