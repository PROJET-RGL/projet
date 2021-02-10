#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"
#include "structure.h"

perso_t init_perso(perso_t perso, int FEN_LARGEUR, int FEN_HAUTEUR, int PERSO_HAUTEUR, int PERSO_LARGEUR)
{
    // Coordonnées du personnage

    perso.perso.x = (FEN_LARGEUR - PERSO_LARGEUR) / 2 - 20;
    perso.perso.y = (FEN_HAUTEUR - PERSO_HAUTEUR) / 2 - 20;

    perso.perso.w = PERSO_LARGEUR;
    perso.perso.h = PERSO_HAUTEUR;

    // Génération des pv du personnage

    perso.pv = 10;

    // Emplacement du personnage dans le lab

    perso.tag = 0;

    return perso;
}

perso_t actualisation_perso(SDL_Renderer *renderer, salle_t salle, porte_t porte, perso_t perso, objet_t tab_obj[N], int VITESSE, int touche1, int touche2)
{
    nettoyage_ecran(renderer);

    if(affichage(renderer, salle.salle , salle.couleur.r, salle.couleur.v, salle.couleur.b) != 1)
    {
        SDL_ExitWithError("Affichage salle raté");
    }

    int i =0;

    for(i = 0; i < N; i++)
    {
        affichage(renderer, salle.tab_obj[i].objet, salle.tab_obj[i].couleur.r, salle.tab_obj[i].couleur.v, salle.tab_obj[i].couleur.b);
    }

    /*
        G = 1                   // on se déplace vers le gauche
        D = 5                   // on se déplace vers la droite
        H = 10                  // on se déplace vers le haut
        B = 20                  // on se déplace vers le bas
        G + D = 1 + 5 = 6       // On annule le mouvement
        G + H = 1 + 10 = 11     // On se déplace en diagonale gauche/haut
        G + B = 1 + 20 = 21     // On se déplace en diagonale gauche/bas
        D + H = 5 + 10 = 15     // On se déplace en diagonale droite/haut
        D + B = 5 + 20 = 25     // on se dépalce en diagonale droite/bas
        H + B = 10 + 20 = 30    // On annule le mouvement
    */

    switch(test_colision(perso.perso, salle.salle, touche1, touche2, VITESSE))
    {
        case 1 :    // Gauche
            perso.perso.x = perso.perso.x - VITESSE;
            break;

        case 5 :    // Droite
            perso.perso.x = perso.perso.x + VITESSE;
            break;

        case 10 :   // Haut
            perso.perso.y = perso.perso.y - VITESSE;
            break;

        case 20 :   // Bas
            perso.perso.y = perso.perso.y + VITESSE;
            break;

        case 11 :   // Gauche - haut
            perso.perso.x = perso.perso.x - VITESSE;
            perso.perso.y = perso.perso.y - VITESSE;
            break;

        case 21 :   // Gauche - bas
            perso.perso.x = perso.perso.x - VITESSE;
            perso.perso.y = perso.perso.y + VITESSE;
            break;

        case 15 :   // Haut - droite
            perso.perso.x = perso.perso.x + VITESSE;
            perso.perso.y = perso.perso.y - VITESSE;
            break;

        case 25 :   // Bas - droite
            perso.perso.x = perso.perso.x + VITESSE;
            perso.perso.y = perso.perso.y + VITESSE;
            break;

        case 50 :   // On colle à gauche
            perso.perso.x = salle.salle.x + 1;
            break;

        case 51 :   // On colle à droite
            perso.perso.x = (salle.salle.x + salle.salle.w) - perso.perso.w - 1;
            break;

        case 52 :   // On colle en haut
            perso.perso.y = salle.salle.y + 1;
            break;

        case 53 :   // On colle en bas
            perso.perso.y = (salle.salle.y + salle.salle.h) - perso.perso.h - 1;
            break;

        default : break;
    }


    if(affichage(renderer, perso.perso, 255, 20, 20) != 1)
    {
        SDL_ExitWithError("Affichage perso raté");
    }

    if(perso.tag != 0 && perso.tag != 6)
    {
        for(i = 0; i < 2; i++)
        {
            if(affichage(renderer, salle.porte[i].porte, 67, 79, 226) != 1)
            {
                SDL_ExitWithError("Affichage porte raté");
            }
        }
    }else{
        if(affichage(renderer, salle.porte[i].porte, 67, 79, 226) != 1)
        {
            SDL_ExitWithError("Affichage porte raté");
        }
    }

    SDL_RenderPresent(renderer);
    return perso;
}
