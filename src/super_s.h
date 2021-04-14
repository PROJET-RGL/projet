#ifndef super_s_H
#define super_s_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <math.h>

/**
 * @brief Structure de données du code
 *
 * \file 'super_s.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
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

typedef struct arme_s arme_t;               // Structure qui gère les arme

typedef struct potion_s potion_t;

typedef struct consommable_s consommable_t;

typedef struct couleur_s couleur_t;         // Structure Couleur

typedef struct velocite_s velocite_t;       // Structure velocité

typedef struct salle_s salle_t;             // Structure salles

typedef struct labyrinthe_s labyrinthe_t;   // Structure Labyrinthe

typedef struct porte_s porte_t;             // Structure Porte

typedef struct perso_s perso_t;             // Structure perso

typedef struct mob_s mob_t;                 // Structure mob

typedef struct objet_s objet_t;             // Structure Objet

typedef struct texture_s texture_t;         // Structure Texture

typedef struct hud_s hud_t;                 // Structure HUD

typedef struct cases_s cases_t;             // Structure cases inventaire

typedef struct inventaire_s inventaire_t;   // Structure Inventaire

typedef struct jeu_s jeu_t;                 // Structure jeu


/**
 * @brief Stucture de la configuration d'une arme, possédant un tag, ainsi qu'un nom et une description. Avec son rayon de portée, les dommages, le cooldown, le stockage possible et la durabilité de l'arme. La rareté de l'arme et son type.
 * 
 */

struct arme_s               // Création d'une arme
{
    int tag;                /*!<    Tag de l'arme */
    char *nom_arme;         /*!<    Nom de l'arme */
    char *descrip;          /*!<    Description de l'arme */
    int rayon;              /*!<    Rayon d'attaque de l'arme */
    int dmg;                /*!<    Dommage causées par l'arme */
    int cooldown;           /*!<    Cooldown de l'arme */
    int munition;           /*!<    Stockage actuel de l'arme */
    int durabilite;         /*!<    Durabilité de l'arme */
    int type;               /*!<    Type de l'arme soit 0 pour cac, soit 1 pour distance */
    int rarete;             /*!<    Rareté de l'arme */
};

struct potion_s
{
    char *nom;
    int cooldown;
    SDL_Rect potion;
    int nb_potion;
};

struct consommable_s
{
    potion_t potion[50];
    arme_t arme[50];
};


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

struct cases_s
{
    SDL_Rect pos_case;    /*!< Coordonnées de la case dans l'inventaire */
    SDL_bool est_vide;    /*!< Indique si la case est vide */
    int item_actuel;
};

struct inventaire_s
{
    SDL_Rect pos_inventaire;                    /*!< Coordonnées de l'inventaire */
    SDL_Texture *texture_inventaire;            /*!< Texture des cases */
    SDL_Rect pos_inventaire_armes;              /*!< Coordonnées de l'inventaire */
    SDL_Texture *texture_inventaire_armes;      /*!< Texture des cases */
    SDL_Texture *texture_case;                  /*!< Texture des cases */
    consommable_t loot;                         /*!< Loot dans l'inventaire */
    cases_t cases[11];                          /*!< Information sur chaque case de l'inventaire */
};

/**
 * @brief Structure de données de personnage, avec l'emplacement du personnage lié au tag, ses coordonnées, ses points de vies, les coordonnées de l'inventaire, sa vitesse, le nombre d'armes et les armes actives
 * 
 */

struct perso_s              // Création d'un personnage
{
    int tag;                /*!< Emplacement du personnage */
    SDL_Rect perso;         /*!< Coordonnées du personnage */
    int pv;                 /*!< Le nombre de vie restant du perosnnage */
    velocite_t velocite;    /*!< Vitesse relative du personnage */
    inventaire_t inv;       /*!< Inventaire */
    arme_t tab_arme[2];     /*!< Tableau d'armes actives*/
    int nb_arme;            /*!< Nombre d'armes que le personnage possède */
    int arme_actuelle;      /*!< Arme dans la main du perso */
    int argent;             /*!< Quantité d'argent du personnage */
    int score;              /*!< Score du joueur */
};

/**
 * @brief Struture de données d'un PNJ, avec ses coordonnées, ses points de vies, et sa texture
 * 
 */

struct mob_s // Création d'un mob
{
    SDL_Rect mob;         /*!< Coordonées du mob en question */
    int pv;               /*!< PV du mob */
    int statue;           /*!< Indique si le mob est en vie */
    // int taille;           /*!< Taille du mob */
    SDL_Texture *texture; /*!< Texture du mob */
};

/**
 * @brief Struture de données d'un objet, avec ses coordonnées, sa texture, la salle dans laquel il se situe, et sa couleur, sous code RGB
 * 
 */

struct objet_s              // Création de l'objet
{
    SDL_Rect objet;         /*!< Coordonées de l'objets en question */
    SDL_Texture *texture;   /*!< Texture de l'objet en question */
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
    int nb_porte;           /*!< Nombre de porte */
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

/**
 * @brief Structure de données pour afficher le HUD (barre de vie, arme etc...)
 * 
 */

struct hud_s                // Création du HUD
{
    SDL_Rect barre_pv;      /*!< Coordonnées de la barre de vie */
    SDL_Surface *img_pv[10];   /*!< Série de 10 image pour la barre de vie */
    SDL_Rect item_dist;     /*!< Coordonnées item Dist */
    SDL_Surface *arme_dist; /*!< Image à charger pour l'arme à distance icone */
    SDL_Rect item_cac;      /*!< Coordonnées item CaC  */
    SDL_Surface *arme_cac; /*!< Image à charger pour l'arme à cac icone */
};

/**
 * @brief Structure de données de jeu, comprennant la structure personnage, et labyrinthe, cette structure sert surtout pour le système de sauvegarde
 * 
 */

struct jeu_s                // Création d'un jeu
{
    perso_t perso;              /*!< Personnage */
    labyrinthe_t lab;           /*!< Labyrinthe */
    hud_t hud;                  /*!< HUD du joueur */         
};

#endif