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

objet_t init_obj(objet_t obj)
{

    obj.couleur.r = rand() % 255;
    obj.couleur.v = rand() % 255;
    obj.couleur.b = rand() % 255;

    obj.objet.w = 50;
    obj.objet.h = 50;

    int x = 144 + (rand() % (1152 - obj.objet.w));
    int y = 90 + (rand() % (720 - obj.objet.h));

    obj.objet.x = x;
    obj.objet.y = y;

    return obj;
}