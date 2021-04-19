#include "item.h"

/**
 * \brief Fichier qui influe sur la création d'items du programme
 * \file 'item.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief Sert à la création de potions, avec son nom, son cooldown et son emplacement dans l'inventaire
 * 
 * @param jeu Structure contenant les caractéristiques d'une potion
 * @param nom Attribut pour reconnaitre une potion
 * @param cooldown Temps écoulé entre chaque utilisation d'une potion
 * @param potion Objet permettant d'obtenir de la vie après une utilisation
 * @param i Emplacement de la potion dans l'inventaire
 * @return potion_t On retourne la potion en question
 */

potion_t new_potion(jeu_t *jeu, char *nom, int cooldown, SDL_Rect potion, int i)
{
    (*jeu).perso.inv.loot.potion[i].nom = nom;
    (*jeu).perso.inv.loot.potion[i].cooldown = cooldown;
    (*jeu).perso.inv.loot.potion[i].potion = potion;
    (*jeu).perso.inv.loot.potion[i].tag = i;

    return (*jeu).perso.inv.loot.potion[i];
}

/**
 * @brief Sert à la création d'armes, avec son nom, son tag, son nom, sa description, son rayon, les dommages, son cooldown, les munitions, sa durabilité, son type, sa rareté et l'arme voulu
 * 
 * @param jeu Structure contenant les caractéristiques d'une arme
 * @param tag Tag unique de l'arme
 * @param nom Attribut pour reconnaitre une arme
 * @param desc Caractéristiques détaillant l'utilisation d'une arme
 * @param rayon Zone d'action d'une arme
 * @param dmg Dégats qu'une arme fait en fonction de la zone d'action (clic gauche/clic droit)
 * @param cooldown Temps écoulé entre chaque utilisation d'une attaque
 * @param munition Stockage d'une nombre de munitions utilisable par une arme
 * @param durabilite Durabilité physique de l'arme
 * @param type Type de l'arme (Corps à corps/Distance)
 * @param rarete Rareté de l'arme
 * @param arme Objet permettant d'attaquer des ennemis pour se défendre
 * @return arme_t On retourne l'arme en question
 */

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

    // AJOUT DE L'AFFICHAGE TEXTURE DE L'ARME

    return (*jeu).perso.inv.loot.arme[tag];
}

