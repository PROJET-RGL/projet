#include "arme.h"

arme_t init_arme1(arme_t arme)
{
    arme.tag = 0;

    arme.nom_arme = "Pistolet";
    arme.descrip = "Le pistolet de base";

    arme.rayon = 300;
    arme.dmg = 5;
    arme.cooldown = 1;

    arme.munition = 10000;
    arme.durabilite = 0;

    arme.type = 'D';
    arme.rarete = 0;

    return arme;
}

arme_t init_arme2(arme_t arme)
{
    arme.tag = 1;

    arme.nom_arme = "Épée";
    arme.descrip = "L'épée de base";

    arme.rayon = 100;
    arme.dmg = 5;
    arme.cooldown = 1;

    arme.munition = 0;
    arme.durabilite = 10000;

    arme.type = 'C';
    arme.rarete = 0;

    return arme;
}

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