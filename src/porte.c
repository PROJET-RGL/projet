#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <time.h>

#include "porte.h"
#include "structure.h"

porte_t init_porte(porte_t porte, int x, int y, int salle_actuel, int salle_dest, int position)
{
    if(position == 'V')
    {
        porte.porte.w = 20;
        porte.porte.h = 150;
    }else if(position == 'H')
    {
        porte.porte.w = 150;
        porte.porte.h = 20;
    }

    porte.porte.x = x;
    porte.porte.y = y - (porte.porte.h/2);

    porte.salle_entree = salle_actuel;
    porte.salle_dest = salle_dest;
    porte.position = position;

    return porte;
}

int collision_porte(perso_t perso, porte_t porte, int salle_actuel, int salle_dest, int VITESSE)
{
    /*
        Si perso.x + perso.w > porte.x && perso.x < salleorte.x + porte.w && perso.y + perso.h < porte.y && perso.y < porte.y + porte.h 
        Alors on est dans le rectangle donc on change le tag de la salle du personnage
    */

    if((perso.perso.x + perso.perso.w + VITESSE) > porte.porte.x && (perso.perso.x + VITESSE) < (porte.porte.x + porte.porte.w) && (perso.perso.y + perso.perso.h + VITESSE) > porte.porte.y && (perso.perso.y + VITESSE) < (porte.porte.y + porte.porte.h))
    {    // on change de salle qui est entrée en paramètre
        return salle_dest;
    }else return salle_actuel;
}

