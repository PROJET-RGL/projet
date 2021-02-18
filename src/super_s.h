#ifndef super_s_H
#define super_s_H

#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <time.h>

/**
 * \brief Header des structures du programmes
 * \file 'super_s.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.1
 * \date 18 Février 2020
 */

// ------------------------------------- DEFINE POUR STRUCTURE ------------------------------------- //

#define O 100   // Taille objet
#define M 100   // Nbre d'objet
#define P 100   // Nbre de porte max
#define S 100   // Nbre salle
#define TAILLE_LAB 7 // Définition de la taille d'un ensemble de salle
#define NB_OBJET 5     // Nombre d'objet dans une salle
#define NB_MOB 5     // Nombre d'objet dans une salle

// ----------------------------- STRUCTURE DE DONNÉES ----------------------------- //

typedef struct couleur_s couleur_t;

typedef struct velocite_s velocite_t;

typedef struct salle_s salle_t;

typedef struct labyrinthe_s labyrinthe_t;

typedef struct porte_s porte_t;

typedef struct perso_s perso_t;

typedef struct mob_s mob_t;

typedef struct objet_s objet_t;

/**
 * @brief Definition de la structure vitesse d'un objet
 */

struct velocite_s           // Le vecteur vitesse du personnage
{
    int x;                  /*!< Vitesse horizontale */
    int y;                  /*!< Vitesse verticale */
};

/**
 * @brief Structure de données des couleurs, avec le code RGB
 * 
 */

struct couleur_s            // Structure définissant la couleur d'un objet
{
    int r;                  /*!< Couleur rouge */
    int v;                  /*!< Couleur vert */
    int b;                  /*!< Couleur bleu */
};

/**
 * @brief Structure de données d'une porte, avec ses coordonnées, sa salle d'entrée, sa salle de sortie et son orientation
 * 
 */

struct porte_s              // Création de la porte en fonction de l'emplacement et deux salles
{
    SDL_Rect porte;         /*!< Coordonnées de la porte */
    int salle_entree;       /*!< Tag de la salle actuel */
    int salle_dest;         /*!< Tag de la salle dest */
    int position;           /*!< Vertical ou Horizontal */
};

/**
 * @brief Structure de données de perosnnage, avec l'emplacement du personnage lié au tag, ses coordonnées, ses points de vies, les coordonnées de l'inventaire et sa vitesse
 * 
 */

struct perso_s              // Création d'un personnage
{
    int tag;                /*!< Emplacement du personnage */
    SDL_Rect perso;         /*!< Coordonnées du personnage */
    int pv;                 /*!< Le nombre de vie restant du perosnnage */
    SDL_Rect inv;           /*!< Affichage de l'inventaire */
    velocite_t velocite;    /*!< Vitesse relative du personnage */
};

/**
 * @brief Struture de données d'un PNJ, avec ses coordonnées, ses points de vies, et sa texture
 * 
 */

struct mob_s                // Création d'un mob
{
    SDL_Rect mob;           /*!< Coordonées du mob en question */
    int pv;                 /*!< PV du mob */
    SDL_Texture *texture;   /*!< Texture du mob */
};

/**
 * @brief Struture de données d'un objet, avec ses coordonnées, sa texture, la salle dans laquel il se situe, et sa couleur, sous code RGB
 * 
 */

struct objet_s              // Création de l'objet
{
    SDL_Rect objet;         /*!< Coordonées de l'objets en question */
    SDL_Texture *text_objet;/*!< Texture de l'objet en question */
    int salle;              /*!< Salle dans laquel l'objet est situé */
    couleur_t couleur;      /*!< Couleur de l'objet */
};

/**
 * @brief Struture de données d'une salle, avec ses coordonnées, son identifiant, son nombre d'objet, son nombre de PNJ, son nombre de PNJ morts, un tableau d'objet,
 * un tableau de PNJ, un tableau de porte et sa couleur
 */

struct salle_s              // Création de la salle avec ses stats
{
    SDL_Rect salle;         /*!< Les coordonnées de la salle */
    int tag_salle;          /*!< Le tag de la salle en question */
    int nb_objt;            /*!< Le nombre d'objet de la salle */
    int nb_mob;             /*!< Le nombre de PNJ dans la salle */
    int nb_mob_mort;        /*!< Le nombre de PNJ mort dans la salle */
    objet_t tab_obj[O];     /*!< Le tableau d'objet de la salle en question */
    mob_t tab_mob[M];       /*!< Le tableau de mob de la salle en question */
    porte_t porte[P];       /*!< Le tableau des portes de la salle en question */
    couleur_t couleur;      /*!< Couleur des bordures de la salle */
};

/**
 * @brief Struture de données d'un labyrinthe de salle, avec sa taille (nombre de salle) et un tableau de salle et sa texture
 * 
 */

struct labyrinthe_s         // Création du labyrinthe en fonction des salles
{
    int nb;                 /*!< Nombre de salle */
    salle_t tab_salle[S];   /*!< Tableau de salle */
    SDL_Texture *texture;   /*!< Texture du fond */
};

#endif