#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <time.h>

#include "fonction_admin.h"
#include "structure.h"
#include "mob.h"


mob_t init_mob(mob_t mob)
{
    // Coordonnées des mobs

    mob.mob.w = 50;
    mob.mob.h = 50;

    int x = 144 + (rand() % (1152 - mob.mob.w));
    int y = 90 + (rand() % (720 - mob.mob.h));

    mob.mob.x = x;
    mob.mob.y = y;

    // Génération des pv du personnage

    mob.pv = 10;

    return mob;
}