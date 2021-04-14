#include "item.h"

potion_t new_potion(jeu_t *jeu, char *nom, int cooldown, SDL_Rect potion, int i)
{
    (*jeu).perso.inv.loot.potion[i].nom = nom;
    (*jeu).perso.inv.loot.potion[i].cooldown = cooldown;
    (*jeu).perso.inv.loot.potion[i].potion = potion;

    return (*jeu).perso.inv.loot.potion[i];
}

arme_t new_arme(jeu_t *jeu, int tag, char *nom, char *desc, int rayon, int dmg, int cooldown, int munition, int durabilite, int type, int rarete, SDL_Rect arme)
{
    (*jeu).perso.inv.loot.arme[tag].tag = tag;
    (*jeu).perso.inv.loot.arme[tag].nom_arme = nom;
    (*jeu).perso.inv.loot.arme[tag].descrip = desc;
    (*jeu).perso.inv.loot.arme[tag].rayon = rayon;
    (*jeu).perso.inv.loot.arme[tag].dmg = dmg;
    (*jeu).perso.inv.loot.arme[tag].cooldown = cooldown;
    (*jeu).perso.inv.loot.arme[tag].munition = munition;
    (*jeu).perso.inv.loot.arme[tag].durabilite = durabilite;
    (*jeu).perso.inv.loot.arme[tag].type = type;
    (*jeu).perso.inv.loot.arme[tag].rarete = rarete;

    return (*jeu).perso.inv.loot.arme[tag];
}

