#ifndef item_H
#define item_H

#include "super.h"

potion_t new_potion(jeu_t *jeu, char *nom, int cooldown, SDL_Rect potion, int i);

arme_t new_arme(jeu_t *jeu, int tag, char *nom, char *desc, int rayon, int dmg, int cooldown, int munition, int durabilite, int type, int rarete, SDL_Rect potion);

#endif