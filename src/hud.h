#ifndef hud_H
#define hud_H

#include "super.h"
#include "fonction_admin.h"

jeu_t init_hud(jeu_t *jeu);

jeu_t init_texture_hud(jeu_t *jeu);

void affichage_hud(SDL_Renderer *renderer, jeu_t *jeu);

#endif