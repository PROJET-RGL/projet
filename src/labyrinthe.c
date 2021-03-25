#include "labyrinthe.h"

/**
 * \brief Fonction qui agis sur le labyrinthe
 * \file 'labyrinthe.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief On définit le labyrinthe avec sa taille, et ses salles
 * 
 * @param lab Importation du labyrinthe à modifier
 * @param taille Définition de la taille du lab
 * @param fen Fenetre d'affichage
 * @param renderer Rendu où l'on va coller la texture
 * @param fenetre Rectangle ayant les coordonnées de l'image
 * @return labyrinthe_t - on retourne le labyrinthe complet
 */

labyrinthe_t init_lab(labyrinthe_t lab, SDL_Window *fen, SDL_Renderer *renderer, SDL_Rect fenetre, int taille)
{

    SDL_Surface *image;

    // Le nombre de salle dans le lab

    lab.nb = taille;

    // Création des salles

    int i = 0;

    for(i = 0; i < taille; i++)
    {
        lab.tab_salle[i] = init_salle(lab.tab_salle[i], fen, renderer, i);
    }

    // ------------------------------------------- Initialisation de la texture des salles !!! ------------------------------------------- //

    image = SDL_LoadBMP("../src/img/Salle.bmp");

    if(image == NULL)
    {
        clean_ressources(fen, renderer, NULL);
        SDL_ExitWithError("Erreur du chargement de l'image");
    }

    lab.texture = SDL_CreateTextureFromSurface(renderer, image);

    if(lab.texture == NULL)
        {
            clean_ressources(fen, renderer, lab.texture);
            SDL_ExitWithError("Erreur de création de la texture");
        }

    if(SDL_QueryTexture(lab.texture, NULL, NULL, &fenetre.w, &fenetre.h) != 0)
        {
            clean_ressources(fen, renderer, lab.texture);
            SDL_ExitWithError("Erreur de chargement de la texture");
        }

    SDL_FreeSurface(image);


    return lab;
}