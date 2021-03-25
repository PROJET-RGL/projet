#include "salle.h"

/**
 * \brief Fichier qui influe sur les salles du programme
 * \file 'salle.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 mars 2021
 */

/**
 * @brief Initialisation de la fenêtre
 * 
 * @param fen Creation de la fenetre
 * @param renderer Création du rendu
 * @return int - Retourne 1 en cas de réussite sinon faux
 */

int creation_fen(SDL_Window **fen, SDL_Renderer **renderer)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("Erreur du chargement du SDL");
    }

    if(SDL_CreateWindowAndRenderer(FEN_LARGEUR, FEN_HAUTEUR, 0, fen, renderer) != 0)
    {
        SDL_ExitWithError("Erreur de création de la fenêtre + le rendu");
    }

    return 1;
}

/**
 * @brief Initialisation d'une salle avec ses caractéristiques
 * 
 * @param fen Fenètre d'acquisition
 * @param renderer Rendu d'acquisition
 * @param salle Importation de la salle à modifier
 * @param tag Attribution de l'identifiant de la salle
 * @return salle_t - Retourne la salle complète avec ses caractéristiques
 */

salle_t init_salle(salle_t salle, SDL_Window *fen, SDL_Renderer *renderer, int tag)
{
    // Ininitalisation des couleurs

    salle.couleur.r = rand() % 255;
    salle.couleur.v = rand() % 255;
    salle.couleur.b = rand() % 255;

    // Initialisation des coordonnées

    salle.salle.x = (FEN_LARGEUR - SALLE_LARGEUR)/2;
    salle.salle.y = (FEN_HAUTEUR - SALLE_HAUTEUR)/2;

    salle.salle.w = SALLE_LARGEUR;
    salle.salle.h = SALLE_HAUTEUR;

    // Initialisation des objets de la salle

    SDL_Surface *image;

    switch(DIFFICULTY)
    {
        case 'P':
            image = SDL_LoadBMP("../src/img/mob_p.bmp");
            break;

        case 'M':
            image = SDL_LoadBMP("../src/img/mob_m.bmp");
            break;

        case 'G':
            image = SDL_LoadBMP("../src/img/mob_g.bmp");
            break;
    }

    int i, j;

    for(i = 0; i < NB_OBJET; i++)
    {
        salle.tab_obj[i] = init_obj(salle.tab_obj[i], fen, renderer, image);

        for(j = 0 ; j < i ; j++)
        {
            salle.tab_obj[i] = compare_objet(salle.tab_obj[j], salle.tab_obj[i]);      // Si l'objet 1 rentre dans l'obet 2, alors on réaffecte une valeur de coords.
        }
    }

    salle.nb_objt = NB_OBJET;

    // Initialisation des mobs de la map

    for(i = 0; i < NB_MOB; i++)
    {
        salle.tab_mob[i] = init_mob(salle.tab_mob[i], fen, renderer, image, DIFFICULTY);

        for(j = 0 ; j < i ; j++)
        {
            salle.tab_mob[i] = compare_mob(salle.tab_mob[j], salle.tab_mob[i]);      // Si le PNJ 1 rentre dans le PNJ 2, alors on réaffecte une valeur de coords.
        }
    }
    SDL_FreeSurface(image);

    salle.nb_mob = NB_MOB;
    salle.nb_mob_mort = 0;

    // Initialisation des portes de la salles !

    if(tag == 0)
    {
        salle.porte[0] = init_porte(salle.porte[0], (salle.salle.x + salle.salle.w)/2 - 30, (salle.salle.y), tag, tag + 1, 'H');
        salle.porte[1] = init_porte(salle.porte[1], 0, 0, 0, 0, 0);
        salle.nb_porte = 1;

    }
    else if(0 < tag && tag < TAILLE_LAB - 1)
    {
        salle.porte[0] = init_porte(salle.porte[0], (salle.salle.x + salle.salle.w)/2 - 30, (salle.salle.y + salle.salle.h), tag, tag - 1, 'H');
        salle.porte[1] = init_porte(salle.porte[1], (salle.salle.x + salle.salle.w)/2 - 30, (salle.salle.y), tag, tag + 1, 'H');
        salle.nb_porte = 2;
    }
    else if(tag == TAILLE_LAB - 1)
    {
        salle.porte[0] = init_porte(salle.porte[0], 0, 0, 0, 0, 0);
        salle.porte[1] = init_porte(salle.porte[1], (salle.salle.x + salle.salle.w)/2 - 30, (salle.salle.y + salle.salle.h), tag, tag - 1, 'H');
        salle.nb_porte = 1;
    }

    // Initialisation du tag salle

    salle.tag_salle = tag;

    return salle;
}

/**
 * @brief Test si il y a collision entre les murs de la salle et le personnage
 * 
 * @param perso Importation du personnage à tester
 * @param salle Importation de la bordure de la salle à tester
 * @return perso_t - Retourne toutes les caractéristiques du personnage
 */

perso_t test_colision(perso_t perso, SDL_Rect salle)
{

    if(perso.velocite.x != 0)
    {
        if(((perso.velocite.x + perso.perso.x + perso.perso.w) <= (salle.x + salle.w)) && ((perso.velocite.x + perso.perso.x) >= (salle.x)))      // Si on est entre la gauche et la droite
        {
            perso.perso.x += perso.velocite.x;
        }else{
            if((perso.velocite.x + perso.perso.x + perso.perso.w) >= (salle.x + salle.w))            // Si on dépasse en à droite
                perso.perso.x = (salle.x + salle.w) - perso.perso.w;
            if((perso.velocite.x + perso.perso.x) <= (salle.x))                                      // Si on dépasse en à gauche
                perso.perso.x = salle.x;
        }
    }

    if(perso.velocite.y != 0)
    {
        if(((perso.velocite.y + perso.perso.y + perso.perso.h) <= (salle.y + salle.h)) && ((perso.velocite.y + perso.perso.y) >= (salle.y)))      // Si on est entre le haut et le bas
        {
            perso.perso.y += perso.velocite.y;
        }else{
            if((perso.velocite.y + perso.perso.y + perso.perso.h) >= (salle.y + salle.h))            // Si on dépasse en bas
                perso.perso.y = salle.y + salle.h - perso.perso.h;
            if((perso.velocite.y + perso.perso.y) <= (salle.y))                                      // Si on dépasse en haut
                perso.perso.y = salle.y;
        }
    }

    return perso;
}