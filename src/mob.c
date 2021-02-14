#include "mob.h"

mob_t init_mob(mob_t mob)
{
    // Coordonnées des mobs

    mob.mob.w = 50;
    mob.mob.h = 50;

    int x = 122 + (rand() % (1174 - mob.mob.w));
    int y = 170 + (rand() % (600 - mob.mob.h));

    mob.mob.x = x;
    mob.mob.y = y;

    // Génération des pv du personnage

    mob.pv = 10;

    return mob;
}

mob_t colision_mob(mob_t mob1, perso_t perso)
{
    if(mob1.mob.y < (perso.perso.y + perso.perso.h) && (mob1.mob.y + mob1.mob.h) > perso.perso.y && mob1.mob.x < (perso.perso.x + perso.perso.w) && (mob1.mob.x + mob1.mob.w) > perso.perso.x)
    {
        mob1.pv = 0;            // Si le joueur entre en contact avec le mob, alors il est mort
    }
    return mob1;
}