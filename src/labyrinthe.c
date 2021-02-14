#include "labyrinthe.h"

labyrinthe_t init_lab(labyrinthe_t lab, int taille)
{
    // Le nombre de salle dans le lab

    lab.nb = taille;

    // Création des salles

    int i = 0;

    for(i = 0; i < taille; i++)
    {
        lab.tab_salle[i] = init_salle(lab.tab_salle[i], i);
    }

    return lab;
}