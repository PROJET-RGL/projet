#include "mob.h"

/**
 * \brief Fichier contenant les fonctions agissant sur les mobs du programme
 * \file 'mob.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 18 Février 2020
 */

/**
 * @brief Création d'un mob, avec ses coordonnées, sa taille et ses points de vies
 * 
 * @param mob On importe le mob à modifier
 * @return mob_t - Retourne le mob mis en paramètre
 */

mob_t init_mob(mob_t mob, SDL_Window *fen, SDL_Renderer *renderer, SDL_Surface *image)
{
    // Coordonnées des mobs

    mob.mob.w = 50;
    mob.mob.h = 50;

    int x = 122 + (rand() % (1174 - mob.mob.w));
    int y = 170 + (rand() % (600 - mob.mob.h));

    mob.mob.x = x;
    mob.mob.y = y;

    // Génération des pv du personnage

    mob.pv = 10;

    // ------------------------------------------- Initialisation des textures mobs ! ------------------------------------------- //

    SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 30, 6, 236));

    if(image == NULL)
    {
        clean_ressources(fen, renderer, NULL);
        SDL_ExitWithError("Erreur du chargement de l'image");
    }

    mob.texture = SDL_CreateTextureFromSurface(renderer, image);

    if(mob.texture == NULL)
        {
            clean_ressources(fen, renderer, mob.texture);
            SDL_ExitWithError("Erreur de création de la texture");
        }

    if(SDL_QueryTexture(mob.texture, NULL, NULL, &mob.mob.w, &mob.mob.h) != 0)
        {
            clean_ressources(fen, renderer, mob.texture);
            SDL_ExitWithError("Erreur de chargement de la texture");
        }

    return mob;
}

/**
 * @brief Vérifie si le joueur est en contact avec un mob et le tue si c'est le cas
 * 
 * @param mob1 On importe les données du mob
 * @param perso On importe les données du joueur
 * @return mob_t - Retourne le mob modifier/pas
 */

mob_t colision_mob(mob_t mob1, perso_t perso)
{
    if(mob1.mob.y < (perso.perso.y + perso.perso.h) && (mob1.mob.y + mob1.mob.h) > perso.perso.y && mob1.mob.x < (perso.perso.x + perso.perso.w) && (mob1.mob.x + mob1.mob.w) > perso.perso.x)
    {
        mob1.pv = 0;            // Si le joueur entre en contact avec le mob, alors il est mort
    }
    return mob1;
}

/**
 * @brief Comparaison entre deux mobs (On vérifie si ils sont en superposé, si c'est le cas, on modifie la position du deuxième mob)
 * 
 * @param obj1 On importe l'objet de référence
 * @param obj2 On importe l'objet tester
 * @return objet_t - Retourne l'objet modifier/pas
 */

mob_t compare_mob(mob_t mob1, mob_t mob2)
{
    while(mob1.mob.y < (mob2.mob.y + mob2.mob.h) && (mob1.mob.y + mob1.mob.h) > mob2.mob.y && mob1.mob.x < (mob2.mob.x + mob2.mob.w) && (mob1.mob.x + mob1.mob.w) > mob2.mob.x)
    {    // Tant que le carré A est en contact avec le carré B
        mob2.mob.x = 122 + (rand() % (1174 - mob2.mob.w));
        mob2.mob.y = 170 + (rand() % (560 - mob2.mob.h));
    }
    return mob2;
}