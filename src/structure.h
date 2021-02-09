#ifndef structure_H
#define structure_H

#define O 3 // Taille objet
#define M 5 // Nbre d'objet
#define P 2 // Nbre de porte max
#define S 7 // Nbre salle

typedef struct salle_s salle_t;

typedef struct labyrinthe_s labyrinthe_t;

typedef struct porte_s porte_t;

typedef struct perso_s perso_t;

typedef struct mob_s mob_t;

typedef struct objet_s objet_t;

typedef struct couleur_s couleur_t;

struct couleur_s            // Structure définissant la couleur d'un objet
{
    int r;                  // Couleur rouge
    int v;                  // Couleur vert
    int b;                  // Couleur bleu
};

struct porte_s              // Création de la porte en fonction de l'emplacement et deux salles
{
    SDL_Rect porte;         // Coordonnées de la porte
    int salle_entree;       // Tag de la salle actuel
    int salle_dest;         // Tag de la salle dest
    int position;           // Vertical ou Horizontal
};

struct perso_s              // Création d'un personnage
{
    int tag;                // Emplacement du personnage
    SDL_Rect perso;         // Coordonnées du personnage
    int pv;                 // Le nombre de vie restant du perosnnage
};

struct mob_s                // Création d'un mob
{
    SDL_Rect mob;           // Coordonées du mob en question
    int pv;                 // PV du mob
};

struct objet_s              // Création de l'objet
{
    SDL_Rect objet;         // Coordonées de l'objets en question
    SDL_Texture *text_objet;     // Texture de l'objet en question
    int salle;              // Salle dans laquel l'objet est situé
    couleur_t couleur;
};

struct salle_s              // Création de la salle avec ses stats
{
    SDL_Rect salle;         // les coordonnées de la salle
    int tag_salle;          // Le tag de la salle en question
    objet_t tab_obj[O];     // le tableau d'objet de la salle en question
    mob_t tab_mob[M];       // le tableau de mob de la salle en question
    porte_t porte[P];       // le tableau des portes de la salle en question
    couleur_t couleur;
};

struct labyrinthe_s         // Création du labyrinthe en fonction des salles
{
    int nb;                 // Nombre de salle
    salle_t tab_salle[S];   // Tableau de salle
};

#endif