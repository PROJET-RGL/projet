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