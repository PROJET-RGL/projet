#include "sauvegarde.h"

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

    }else
    {
        printf("Erreur de sauvegarde veuillez rééssayer !\n");
    }

    fclose(fichier);
}

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

        fscanf(fichier, "%d ", &(*jeu).perso.tag);
        fscanf(fichier, "%d %d %d %d ", &(*jeu).perso.perso.x, &(*jeu).perso.perso.y, &(*jeu).perso.perso.w, &(*jeu).perso.perso.h);
        fscanf(fichier, "%d ", &(*jeu).perso.pv);
        fscanf(fichier, "%d %d %d %d ", &(*jeu).perso.inv.x, &(*jeu).perso.inv.y, &(*jeu).perso.inv.w, &(*jeu).perso.inv.h);
        fscanf(fichier, "%d %d ", &(*jeu).perso.velocite.x, &(*jeu).perso.velocite.y);

    }else
    {
        printf("Mauvaise lecture de fichier, veuillez recommencez !\n");
    }
    fclose(fichier);
    return *jeu;
}
