#ifndef super_d_H
#define super_d_H


/**
 * \brief Header des defines du programmes
 * \file 'super_d.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

// ------------------------------------- DEFINE POUR LE MAIN ------------------------------------- //

// Fenêtre dimension

#define FEN_LARGEUR 1440
#define FEN_HAUTEUR 900

// Salle dimension

#define SALLE_LARGEUR (FEN_LARGEUR/12)*10 + 3
#define SALLE_HAUTEUR (FEN_HAUTEUR/12)*8.5

// Personnage Dimension

#define PERSO_LARGEUR 55
#define PERSO_HAUTEUR 79

// Stat globale

#define DELAI 100
#define VITESSE 7
#define MAX_LAB 5

// Booleen

#define TRUE 1
#define FALSE 0

// Statue de l'entité

#define MORT 0
#define VIVANT 1

// DEBUG

#define DEBUG FALSE
#define DEBUG_MODE if(DEBUG)

// Difficulty

#define DIFFICULTY 'G'
#define VITESSE_MOB 2

#endif