#ifndef porte_H
#define porte_H

#include "super.h"

int collision_porte(perso_t perso, porte_t porte, int salle_actuel, int salle_dest);

porte_t init_porte(porte_t porte, int x, int y, int salle_actuel, int salle_dest, int position);

#endif