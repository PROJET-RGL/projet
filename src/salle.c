#include "salle.h"

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

salle_t init_salle(salle_t salle, int tag)
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

    int nbre_objt, i, j;

    nbre_objt = NB_OBJET;

    for(i = 0; i < nbre_objt; i++)
    {
        salle.tab_obj[i] = init_obj(salle.tab_obj[i]);

        for(j = 0 ; j < i ; j++)
        {
            salle.tab_obj[i] = compare_objet(salle.tab_obj[j], salle.tab_obj[i]);      // Si l'objet 1 rentre dans l'obet 2, alors on réaffecte une valeur de coords.
        }
    }

    salle.nb_objt = nbre_objt;

    // Initialisation des mobs de la map

    int nbre_mob;

    nbre_mob = NB_MOB;

    for(i = 0; i < nbre_mob; i++)
    {
        salle.tab_mob[i] = init_mob(salle.tab_mob[i]);
    }

    salle.nb_mob = NB_MOB;
    salle.nb_mob_mort = 0;

    // Initialisation des portes de la salles !

    if(tag == 0)
    {
        salle.porte[0] = init_porte(salle.porte[0], (salle.salle.x + salle.salle.w)/2 - 30, salle.salle.y, tag, tag + 1, 'H');

    }else if(0 < tag && tag < TAILLE_LAB - 1)
    {
        salle.porte[0] = init_porte(salle.porte[0], (salle.salle.x + salle.salle.w)/2 - 30, (salle.salle.y + salle.salle.h), tag, tag - 1, 'H');
        salle.porte[1] = init_porte(salle.porte[1], (salle.salle.x + salle.salle.w)/2 - 30, (salle.salle.y), tag, tag + 1, 'H');
    }else if(tag == TAILLE_LAB - 1)
    {
        salle.porte[1] = init_porte(salle.porte[1], (salle.salle.x + salle.salle.w)/2 - 30, (salle.salle.y + salle.salle.h), tag, tag - 1, 'H');

    }

    // Initialisation du tag salle

    salle.tag_salle = tag;

    return salle;
}

int test_colision(SDL_Rect perso, SDL_Rect salle, int touche1, int touche2)
{
    SDL_Rect persoGHOST;
    int sortie = 0;

    persoGHOST.x = perso.x;
    persoGHOST.y = perso.y;

    persoGHOST.w = perso.w;
    persoGHOST.h = perso.h;

    if(touche1 == 'Q' || touche2 == 'Q')
    {
        persoGHOST.x = perso.x - VITESSE;
        if(persoGHOST.x < salle.x)
        {
            // Nous sommes en dehors, donc c'est pas bon
            sortie = 50;    // Message d'erreur lié au passage de bordure par la gauche
        }else sortie += 1;  // on return 1 car c'est possible de ce déplacer
    }
    if(touche1 == 'D' || touche2 == 'D')
    {
        persoGHOST.x = perso.x + VITESSE;
        if(persoGHOST.x + perso.w > salle.x + salle.w)
        {
            // Nous sommes en dehors, donc c'est pas bon
            sortie = 51;    // Message d'erreur lié au passage de bordure par la droite
        }else sortie += 5;  // on return 1 car c'est possible de ce déplacer
    }
    if(touche1 == 'Z' || touche2 == 'Z')
    {
        persoGHOST.y = perso.y - VITESSE;
        if(persoGHOST.y < salle.y)
        {
            // Nous sommes en dehors, donc c'est pas bon
            sortie = 52;    // Message d'erreur lié au passage de bordure par le haut
        }else sortie += 10; // on return 1 car c'est possible de ce déplacer
    }
    if(touche1 == 'S' || touche2 == 'S')
    {
        persoGHOST.y = perso.y + VITESSE;
        if(persoGHOST.y + perso.h > salle.y + salle.h)
        {
            // Nous sommes en dehors par le bas, donc c'est pas bon
            sortie = 53;    // Message d'erreur lié au passage de bordure par le bas
        }else sortie += 20; // on ajoute 20 à sortie car c'est possible de ce déplacer
    }

    return sortie;
}