#ifndef salle_H
#define salle_H

#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "fonction_admin.h"
#include "perso.h"
#include "objet.h"
#include "porte.h"
#include "labyrinthe.h"
#include "structure.h"
#include "actualisation.h"

int creation_fen(SDL_Window **fen, SDL_Renderer **renderer, int FEN_LARGEUR, int FEN_HAUTEUR);

salle_t init_salle(salle_t salle, int FEN_LARGEUR, int FEN_HAUTEUR, int SALLE_HAUTEUR, int SALLE_LARGEUR, int tag);

int test_colision(SDL_Rect perso, SDL_Rect salle, int touche1, int touche2, int VITESSE);

#endif