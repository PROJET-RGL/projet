#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"
#include "structure.h"

SDL_Texture init_texture(SDL_Renderer **renderer, int HAUTEUR, int LARGEUR, SDL_Rect rect, char c[50]);