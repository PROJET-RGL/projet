#include "fonction_admin.h"

void SDL_ExitWithError(const char *message)
{
    SDL_Log("Erreur : %s > %s \n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void clean_ressources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
    if(t != NULL)
        SDL_DestroyTexture(t);

    if(r != NULL)
        SDL_DestroyRenderer(r);

    if(w != NULL)
        SDL_DestroyWindow(w);
}

void nettoyage_ecran(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

int affichage(SDL_Renderer *renderer, SDL_Rect cible, int r, int v, int b)
{
    SDL_SetRenderDrawColor(renderer, r, v, b, SDL_ALPHA_OPAQUE);

    if(SDL_RenderDrawRect(renderer, &cible) != 0)
    {
        SDL_ExitWithError("Affichage raté pour le rectangle cible !");
    }

    return 1;
}