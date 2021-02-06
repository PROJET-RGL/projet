#ifndef actualisation_H
#define actualisation_H

#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"
#include "structure.h"

perso_t actualisation_salle(labyrinthe_t lab, perso_t perso, SDL_Renderer *renderer, int r, int v, int b, int touche1, int touche2);

#endif