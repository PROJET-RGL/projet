#include "objet.h"

/**
 * \brief Fichier contenant les fonctions agissant sur les objets du programme
 * \file 'objet.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief Création d'un objet, avec ses coordonnées, sa taille et sa couleur
 * 
 * @param obj On importe l'objet à modifier
 * @param fen Fenêtre d'acquisition
 * @param renderer Rendu d'acquisition
 * @param image Importation de la texture de l'objet
 * @return objet_t - Retourne l'objet mis en paramètre
 */

objet_t init_obj(objet_t obj, SDL_Window *fen, SDL_Renderer *renderer, SDL_Surface *image)
{

    obj.couleur.r = rand() % 255;
    obj.couleur.v = rand() % 255;
    obj.couleur.b = rand() % 255;

    obj.objet.w = 50;
    obj.objet.h = 50;

    int x = 122 + (rand() % (1174 - obj.objet.w));
    int y = 170 + (rand() % (600 - obj.objet.h));

    obj.objet.x = x;
    obj.objet.y = y;

    // ------------------------------------------- Initialisation des textures objets ! ------------------------------------------- //

    if(image == NULL)
    {
        clean_ressources(fen, renderer, NULL);
        SDL_ExitWithError("Erreur du chargement de l'image");
    }

    obj.texture = SDL_CreateTextureFromSurface(renderer, image);

    if(obj.texture == NULL)
        {
            clean_ressources(fen, renderer, obj.texture);
            SDL_ExitWithError("Erreur de création de la texture");
        }

    if(SDL_QueryTexture(obj.texture, NULL, NULL, &obj.objet.w, &obj.objet.h) != 0)
        {
            clean_ressources(fen, renderer, obj.texture);
            SDL_ExitWithError("Erreur de chargement de la texture");
        }

    return obj;
}

/**
 * @brief Comparaison entre deux objets (On vérifie si ils sont en superposé, si c'est le cas, on modifie la position du deuxième objet)
 * 
 * @param obj1 On importe l'objet de référence
 * @param obj2 On importe l'objet tester
 * @return objet_t - Retourne l'objet modifier/pas
 */

objet_t compare_objet(objet_t obj1, objet_t obj2)
{
    while(obj1.objet.y < (obj2.objet.y + obj2.objet.h) && (obj1.objet.y + obj1.objet.h) > obj2.objet.y && obj1.objet.x < (obj2.objet.x + obj2.objet.w) && (obj1.objet.x + obj1.objet.w) > obj2.objet.x)        
    {    // Tant que le carré A est en contact avec le carré B
        obj2.objet.x = 122 + (rand() % (1174 - obj2.objet.w));
        obj2.objet.y = 170 + (rand() % (560 - obj2.objet.h));
    }
    return obj2;
}