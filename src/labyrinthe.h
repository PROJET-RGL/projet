#ifndef labyrinthe_H
#define labyrinthe_H

#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <time.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"
#include "objet.h"
#include "structure.h"

labyrinthe_t init_lab(labyrinthe_t lab, int taille, int FEN_LARGEUR, int FEN_HAUTEUR, int SALLE_HAUTEUR, int SALLE_LARGEUR);


#endif