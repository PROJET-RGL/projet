#ifndef hud_H
#define hud_H

#include "super.h"
#include "fonction_admin.h"
#include "texture.h"

jeu_t init_hud(jeu_t *jeu);

jeu_t init_texture_hud(jeu_t *jeu);

void affichage_hud(SDL_Renderer *renderer, jeu_t *jeu, SDL_Window *fen);

void ouvrir_inventaire(SDL_Renderer *renderer, SDL_Window *fen, jeu_t *jeu, SDL_bool plein_ecran);

int position_inventaire(jeu_t *jeu, SDL_Event event);

#endif