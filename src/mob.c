#include "mob.h"

/**
 * \brief Fichier contenant les fonctions agissant sur les mobs du programme
 * \file 'mob.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief Création d'un mob, avec ses coordonnées, sa taille et ses points de vies
 * 
 * @param mob On importe le mob à modifier
 * @return mob_t - Retourne le mob mis en paramètre
 */

mob_t init_mob(mob_t mob, SDL_Window *fen, SDL_Renderer *renderer, SDL_Surface *image, int taille)
{
    switch(taille)
    {
        case 'P':
            mob.mob.w = 50;
            mob.mob.h = 50;
            mob.pv = 10;
            break;

        case 'M':
            mob.mob.w = 100;
            mob.mob.h = 100;
            mob.pv = 20;
            break;

        case 'G':
            mob.mob.w = 150;
            mob.mob.h = 150;
            mob.pv = 30;
            break;
    }

    // Coordonnées des mobs

    int x = 122 + (rand() % (1174 - mob.mob.w));
    int y = 170 + (rand() % (600 - mob.mob.h));

    mob.mob.x = x;
    mob.mob.y = y;

    // Génération des pv du personnage

    mob.statue = VIVANT;

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

int colision_mob(mob_t mob1, perso_t perso)
{
    if(mob1.mob.y < (perso.perso.y + perso.perso.h) && (mob1.mob.y + mob1.mob.h) > perso.perso.y && mob1.mob.x < (perso.perso.x + perso.perso.w) && (mob1.mob.x + mob1.mob.w) > perso.perso.x)
        return 1;
    else return 0;
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

SDL_Rect deplacement_mob(SDL_Rect perso, SDL_Rect mob, int i)
{
    int pointpersox = (perso.x + (perso.w/2));
    int pointpersoy = (perso.y + (perso.h/2));

    int pointmobx = (mob.x + (mob.w/2));
    int pointmoby = (mob.y + (mob.h/2));

    int signeX = pointpersox - pointmobx;
    int signeY = pointpersoy - pointmoby;

    if(signeX > 0)                                  // Si mob.x > 
    {
        if(signeX < VITESSE_MOB)
        {
            mob.x += (pointpersox - pointmobx);
        }
        mob.x += VITESSE_MOB;

    }else
    if(signeX < 0)
    {
        if(signeX > -VITESSE_MOB)
        {
            mob.x -= (pointmobx - pointpersox);
        }
        mob.x -= VITESSE_MOB;
    }

    if(signeY > 0)
    {
        if(signeY < VITESSE_MOB)
        {
            mob.y += (pointpersoy - pointmoby);
        }
        mob.y += VITESSE_MOB;

    }else
    if(signeY < 0)
    {
        if(signeY > -VITESSE_MOB)
        {
            mob.y -= (pointmoby - pointpersoy);
        }
        mob.y -= VITESSE_MOB;
    }

    return mob;
}