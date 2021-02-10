#ifndef objet_H
#define objet_H

#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <time.h>

#include "salle.h"
#include "fonction_admin.h"
#include "perso.h"
#include "porte.h"
#include "labyrinthe.h"
#include "structure.h"

objet_t init_obj(objet_t obj);

objet_t compare_objet(objet_t obj1, objet_t obj2);

#endif