#include "arme.h"

/**
 * \brief Fonction d'initialisation des armes du programme
 * \file 'arme.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 mars 2021
 */

/**
 * @brief On créer l'arme distance basique
 * 
 * @param arme          L'arme distance basique
 * @return arme_t       On retourne les valeurs initialisé
 */

arme_t init_arme1(arme_t arme)
{
    arme.tag = 0;

    arme.nom_arme = "Pistolet";
    arme.descrip = "Le pistolet de base";

    arme.rayon = 400;
    arme.dmg = 5;
    arme.cooldown = 5;

    arme.munition = 10000;
    arme.durabilite = 0;

    arme.type = 'D';
    arme.rarete = 0;

    return arme;
}

/**
 * @brief On créer l'arme corps à corps basique
 * 
 * @param arme          L'arme corps à corps basique
 * @return arme_t       On retourne les valeurs initialisé
 */

arme_t init_arme2(arme_t arme)
{
    arme.tag = 1;

    arme.nom_arme = "Épée";
    arme.descrip = "L'épée de base";

    arme.rayon = 200;
    arme.dmg = 6;
    arme.cooldown = 1;

    arme.munition = 0;
    arme.durabilite = 10000;

    arme.type = 'C';
    arme.rarete = 0;

    return arme;
}

/**
 * @brief On créer l'arme vide basique
 * 
 * @param arme          L'arme vide basique
 * @return arme_t       On retourne les valeurs nullifié
 */

arme_t init_arme_vide(arme_t arme)
{
    arme.tag = 'V';

    arme.nom_arme = "Vide";
    arme.descrip = "Rien";

    arme.rayon = 0;
    arme.dmg = 0;
    arme.cooldown = 0;

    arme.munition = 0;
    arme.durabilite = 0;

    arme.type = 'V';
    arme.rarete = 0;

    return arme;
}