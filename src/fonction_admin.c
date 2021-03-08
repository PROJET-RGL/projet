#include "fonction_admin.h"

/**
 * \brief Gestion des fenêtres
 * \file 'fonction_admin.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.1
 * \date 18 Février 2020
 */

/**
 * @brief Gestion du message d'erreur
 * 
 * @param message Définition du message d'erreur en console
 */

void SDL_ExitWithError(const char *message)
{
    SDL_Log("Erreur : %s > %s \n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

/**
 * @brief On désallous la mémoire des 3 attributs qui composent la fenêtre
 *
 * @param w La page windows
 * @param r L'apparence de la fenêtre
 * @param t Textures de la fenêtre
 */

void clean_ressources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
    if(t != NULL)
        SDL_DestroyTexture(t);

    if(r != NULL)
        SDL_DestroyRenderer(r);

    if(w != NULL)
        SDL_DestroyWindow(w);
}

/**
 * @brief On éfface le rendu d'une rendu d'une fenêtre active

 * @param renderer Attributs pour la gestion d'une fenêtre
 */

void nettoyage_ecran(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

/**
 * @brief On dessine à l'écran le rectangle ciblé avec en paramètres les couleurs voulues
 * 
 * @param renderer Attributs pour la gestion d'une fenêtre
 * @param cible Rectangle ciblé
 * @param r Couleur Red
 * @param v Couleur Green
 * @param b Couleur Blue
 * @return int - 1 si réussi sinon faux
 */

int affichage(SDL_Renderer *renderer, SDL_Rect cible, int r, int v, int b)
{
    SDL_SetRenderDrawColor(renderer, r, v, b, SDL_ALPHA_OPAQUE);

    if(SDL_RenderDrawRect(renderer, &cible) != 0)
    {
        SDL_ExitWithError("Affichage raté pour le rectangle cible !");
    }

    return SDL_TRUE;
}