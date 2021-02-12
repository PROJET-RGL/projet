#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>

// Fenêtre dimension

#define FEN_LARGEUR 1440
#define FEN_HAUTEUR 900

// Salle dimension

#define SALLE_LARGEUR (FEN_LARGEUR/10)*8 + 45
#define SALLE_HAUTEUR (FEN_HAUTEUR/10)*8 - 80

// Personnage Dimension

#define PERSO_LARGEUR 90
#define PERSO_HAUTEUR 90

// Stat globale

#define DELAI 100
#define VITESSE 5

// Booleen

#define TRUE 1
#define FALSE 0
