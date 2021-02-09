#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"
#include "structure.h"
#include "texture.h"

/*
SDL_Texture init_texture(SDL_Renderer **renderer, int HAUTEUR, int LARGEUR, SDL_Rect rect, char c[50]) // char *c *c = "src/salle.BMP"
{
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;

    image = SDL_LoadBMP(c);               // <---- " ", c

    if(image == NULL)
    {
        SDL_ExitWithError("Erreur du chargement de l'image");
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if(texture == NULL)
    {
        SDL_ExitWithError("Erreur de création de la texture");
    }

    if(SDL_QueryTexture(texture, NULL, NULL, LARGEUR, HAUTEUR) != 0)
    {
        SDL_ExitWithError("Erreur de chargement de la texture");
    }

    return texture;
} */