#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <time.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"
#include "objet.h"
#include "mob.h"
#include "labyrinthe.h"
#include "structure.h"

labyrinthe_t init_lab(labyrinthe_t lab, int taille, int FEN_LARGEUR, int FEN_HAUTEUR, int SALLE_HAUTEUR, int SALLE_LARGEUR)
{
    // Le nombre de salle dans le lab

    lab.nb = taille;

    // Création des salles

    int i = 0;

    for(i = 0; i < taille; i++)
    {
        lab.tab_salle[i] = init_salle(lab.tab_salle[i], FEN_LARGEUR, FEN_HAUTEUR, SALLE_HAUTEUR, SALLE_LARGEUR, i);
    }

    return lab;
}