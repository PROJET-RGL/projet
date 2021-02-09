#ifndef perso_H
#define perso_H

#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "salle.h"
#include "fonction_admin.h"
#include "objet.h"
#include "porte.h"
#include "labyrinthe.h"
#include "structure.h"
#include "actualisation.h"

#define N 3

perso_t init_perso(perso_t perso, int FEN_LARGEUR, int FEN_HAUTEUR, int PERSO_HAUTEUR, int PERSO_LARGEUR);

perso_t actualisation_perso(SDL_Renderer *renderer, salle_t salle, porte_t porte, perso_t perso, objet_t tab_obj[N], int VITESSE, int touche1, int touche2);

#endif