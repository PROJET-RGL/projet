#include "sauvegarde.h"

/**
 * \brief Fichier qui influe sur les salles du programme
 * \file 'sauvegarde.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief Sauvegarde linéaire des différentes données du jeu dans un fichier
 * 
 * @param jeu   Structure actuelle du jeu avec les différentes données à sauvegarder
 */

void sauvegarde(jeu_t *jeu)
{

    FILE* fichier = NULL;

    fichier = fopen("../src/save.txt", "w+");

    // On commence par enregistrer les structures
    if(fichier != NULL )
    {
        int i = 0, j = 0;



        // Structure lab

        fprintf(fichier, "%d ", (*jeu).lab.nb);            // int nb

        for(i = 0; i<TAILLE_LAB; i++)
        {
            // Structure Salle
            fprintf(fichier, "%d %d %d %d ", (*jeu).lab.tab_salle[i].salle.x, (*jeu).lab.tab_salle[i].salle.y, (*jeu).lab.tab_salle[i].salle.w, (*jeu).lab.tab_salle[i].salle.h);             //  sauvegarde des coordonées de la salle
            fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].tag_salle);
            fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].nb_objt);
            fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].nb_mob);
            fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].nb_mob_mort);
            fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].nb_porte);

            for(j = 0; j < (*jeu).lab.tab_salle[i].nb_objt; j++)
            {
                // Structure Objet
                fprintf(fichier, "%d %d %d %d ", (*jeu).lab.tab_salle[i].tab_obj[j].objet.x, (*jeu).lab.tab_salle[i].tab_obj[j].objet.y, (*jeu).lab.tab_salle[i].tab_obj[j].objet.w, (*jeu).lab.tab_salle[i].tab_obj[j].objet.h);
                fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].tab_obj[j].salle);
                fprintf(fichier, "%d %d %d ", (*jeu).lab.tab_salle[i].tab_obj[j].couleur.r, (*jeu).lab.tab_salle[i].tab_obj[j].couleur.v, (*jeu).lab.tab_salle[i].tab_obj[j].couleur.b);
            }

            for(j = 0; j < (*jeu).lab.tab_salle[i].nb_mob; j++)
            {
                // Structure Mob
                fprintf(fichier, "%d %d %d %d ", (*jeu).lab.tab_salle[i].tab_mob[j].mob.x, (*jeu).lab.tab_salle[i].tab_mob[j].mob.y, (*jeu).lab.tab_salle[i].tab_mob[j].mob.w, (*jeu).lab.tab_salle[i].tab_mob[j].mob.h);
                fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].tab_mob[j].pv);
                fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].tab_mob[j].statue);
            }

            for(j = 0; j < (*jeu).lab.tab_salle[i].nb_porte; j++)
            {
                // Structure Porte
                fprintf(fichier, "%d %d %d %d ", (*jeu).lab.tab_salle[i].porte[j].porte.x, (*jeu).lab.tab_salle[i].porte[j].porte.y, (*jeu).lab.tab_salle[i].porte[j].porte.w, (*jeu).lab.tab_salle[i].porte[j].porte.h);
                fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].porte[j].salle_entree);
                fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].porte[j].salle_dest);
                fprintf(fichier, "%d ", (*jeu).lab.tab_salle[i].porte[j].position);
            }

            fprintf(fichier, "%d %d %d ", (*jeu).lab.tab_salle[i].couleur.r, (*jeu).lab.tab_salle[i].couleur.v, (*jeu).lab.tab_salle[i].couleur.b);
        }

        // Structure Perso

        fprintf(fichier, "%d ", (*jeu).perso.tag);
        fprintf(fichier, "%d %d %d %d ", (*jeu).perso.perso.x, (*jeu).perso.perso.y, (*jeu).perso.perso.w, (*jeu).perso.perso.h);
        fprintf(fichier, "%d ", (*jeu).perso.pv);
        fprintf(fichier, "%d %d %d %d ", (*jeu).perso.inv.x, (*jeu).perso.inv.y, (*jeu).perso.inv.w, (*jeu).perso.inv.h);
        fprintf(fichier, "%d %d ", (*jeu).perso.velocite.x, (*jeu).perso.velocite.y);
        fprintf(fichier, "%d ", (*jeu).perso.nb_arme);
        fprintf(fichier, "%d ", (*jeu).perso.arme_actuelle);

        // Structure Arme

        for(i = 0; i <= (*jeu).perso.nb_arme; i++)
        {
                        printf("Test !\n");
            fprintf(fichier, "%d ", (*jeu).perso.tab_arme[i].cooldown);
            // fprintf(fichier, "%s ", (*jeu).perso.tab_arme[i].descrip);
            fprintf(fichier, "%d ", (*jeu).perso.tab_arme[i].dmg);
            fprintf(fichier, "%d ", (*jeu).perso.tab_arme[i].durabilite);
            fprintf(fichier, "%d ", (*jeu).perso.tab_arme[i].munition);
            // fprintf(fichier, "%s ", (*jeu).perso.tab_arme[i].nom_arme);
            fprintf(fichier, "%d ", (*jeu).perso.tab_arme[i].rarete);
            fprintf(fichier, "%d ", (*jeu).perso.tab_arme[i].rayon);
            fprintf(fichier, "%d ", (*jeu).perso.tab_arme[i].tag);
            fprintf(fichier, "%d ", (*jeu).perso.tab_arme[i].type);
        }

        // Structure HUD

        fprintf(fichier, "%d %d %d %d ", (*jeu).hud.barre_pv.x, (*jeu).hud.barre_pv.y, (*jeu).hud.barre_pv.w, (*jeu).hud.barre_pv.h);
        fprintf(fichier, "%d %d %d %d ", (*jeu).hud.item_cac.x, (*jeu).hud.item_cac.y, (*jeu).hud.item_cac.w, (*jeu).hud.item_cac.h);
        fprintf(fichier, "%d %d %d %d ", (*jeu).hud.item_dist.x, (*jeu).hud.item_dist.y, (*jeu).hud.item_dist.w, (*jeu).hud.item_dist.h);


    }else
    {
        printf("Erreur de sauvegarde veuillez rééssayer !\n");
    }

    fclose(fichier);
}

/**
 * @brief   Chargement linéaire des différentes données enregistrer sur un fichier
 *
 * @param jeu   Partie qui va prendre les chargement en question
 * @return jeu_t    On retourne la parte charger
 */

jeu_t chargement(jeu_t *jeu)
{
    FILE* fichier = NULL;

    fichier = fopen("../src/save.txt", "r+");

    if(fichier != NULL)
    {

        int i = 0, j = 0;

        // Structure lab

        fscanf(fichier, "%d ", &(*jeu).lab.nb);            // int nb

        for(i = 0; i<TAILLE_LAB; i++)
        {
            // Structure Salle
            fscanf(fichier, "%d %d %d %d ", &(*jeu).lab.tab_salle[i].salle.x, &(*jeu).lab.tab_salle[i].salle.y, &(*jeu).lab.tab_salle[i].salle.w, &(*jeu).lab.tab_salle[i].salle.h);             //  sauvegarde des coordonées de la salle
            fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].tag_salle);
            fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].nb_objt);
            fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].nb_mob);
            fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].nb_mob_mort);
            fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].nb_porte);

            for(j = 0; j < ((*jeu).lab.tab_salle[i].nb_objt); j++)
            {
                // Structure Objet
                fscanf(fichier, "%d %d %d %d ", &(*jeu).lab.tab_salle[i].tab_obj[j].objet.x, &(*jeu).lab.tab_salle[i].tab_obj[j].objet.y, &(*jeu).lab.tab_salle[i].tab_obj[j].objet.w, &(*jeu).lab.tab_salle[i].tab_obj[j].objet.h);
                fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].tab_obj[j].salle);
                fscanf(fichier, "%d %d %d ", &(*jeu).lab.tab_salle[i].tab_obj[j].couleur.r, &(*jeu).lab.tab_salle[i].tab_obj[j].couleur.v, &(*jeu).lab.tab_salle[i].tab_obj[j].couleur.b);
            }

            for(j = 0; j < ((*jeu).lab.tab_salle[i].nb_mob); j++)
            {
                // Structure Mob
                fscanf(fichier, "%d %d %d %d ", &(*jeu).lab.tab_salle[i].tab_mob[j].mob.x, &(*jeu).lab.tab_salle[i].tab_mob[j].mob.y, &(*jeu).lab.tab_salle[i].tab_mob[j].mob.w, &(*jeu).lab.tab_salle[i].tab_mob[j].mob.h);
                fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].tab_mob[j].pv);
                fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].tab_mob[j].statue);
            }

            for(j = 0; j < ((*jeu).lab.tab_salle[i].nb_porte); j++)
            {
                // Structure Porte
                fscanf(fichier, "%d %d %d %d ", &(*jeu).lab.tab_salle[i].porte[j].porte.x, &(*jeu).lab.tab_salle[i].porte[j].porte.y, &(*jeu).lab.tab_salle[i].porte[j].porte.w, &(*jeu).lab.tab_salle[i].porte[j].porte.h);
                fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].porte[j].salle_entree);
                fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].porte[j].salle_dest);
                fscanf(fichier, "%d ", &(*jeu).lab.tab_salle[i].porte[j].position);
            }

            fscanf(fichier, "%d %d %d ", &(*jeu).lab.tab_salle[i].couleur.r, &(*jeu).lab.tab_salle[i].couleur.v, &(*jeu).lab.tab_salle[i].couleur.b);
        }

        // Structure perso

        fscanf(fichier, "%d ", &(*jeu).perso.tag);
        fscanf(fichier, "%d %d %d %d ", &(*jeu).perso.perso.x, &(*jeu).perso.perso.y, &(*jeu).perso.perso.w, &(*jeu).perso.perso.h);
        fscanf(fichier, "%d ", &(*jeu).perso.pv);
        fscanf(fichier, "%d %d %d %d ", &(*jeu).perso.inv.x, &(*jeu).perso.inv.y, &(*jeu).perso.inv.w, &(*jeu).perso.inv.h);
        fscanf(fichier, "%d %d ", &(*jeu).perso.velocite.x, &(*jeu).perso.velocite.y);
        fscanf(fichier, "%d ", &(*jeu).perso.nb_arme);
        fscanf(fichier, "%d ", &(*jeu).perso.arme_actuelle);

        // Structure Arme

        for(i = 0; i <= (*jeu).perso.nb_arme; i++)
        {
            fscanf(fichier, "%d ", &(*jeu).perso.tab_arme[i].cooldown);
            // fscanf(fichier, "%s ", *(&(*jeu).perso.tab_arme[i].descrip));
            fscanf(fichier, "%d ", &(*jeu).perso.tab_arme[i].dmg);
            fscanf(fichier, "%d ", &(*jeu).perso.tab_arme[i].durabilite);
            fscanf(fichier, "%d ", &(*jeu).perso.tab_arme[i].munition);
            // fscanf(fichier, "%s ", *(&(*jeu).perso.tab_arme[i].nom_arme));
            fscanf(fichier, "%d ", &(*jeu).perso.tab_arme[i].rarete);
            fscanf(fichier, "%d ", &(*jeu).perso.tab_arme[i].rayon);
            fscanf(fichier, "%d ", &(*jeu).perso.tab_arme[i].tag);
            fscanf(fichier, "%d ", &(*jeu).perso.tab_arme[i].type);

        }

        // Structure HUD

        fscanf(fichier, "%d %d %d %d ", &(*jeu).hud.barre_pv.x, &(*jeu).hud.barre_pv.y, &(*jeu).hud.barre_pv.w, &(*jeu).hud.barre_pv.h);
        fscanf(fichier, "%d %d %d %d ", &(*jeu).hud.item_cac.x, &(*jeu).hud.item_cac.y, &(*jeu).hud.item_cac.w, &(*jeu).hud.item_cac.h);
        fscanf(fichier, "%d %d %d %d ", &(*jeu).hud.item_dist.x, &(*jeu).hud.item_dist.y, &(*jeu).hud.item_dist.w, &(*jeu).hud.item_dist.h);

    }else
    {
        printf("Mauvaise lecture de fichier, veuillez recommencez !\n");
    }
    fclose(fichier);
    return *jeu;
}
