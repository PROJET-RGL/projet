#include "combat.h"

int test_clique_gauche(jeu_t *jeu)
{
    int persox = (*jeu).perso.perso.x;
    int persoy = (*jeu).perso.perso.y;
    int persow = (*jeu).perso.perso.w;
    int persoh = (*jeu).perso.perso.h;

    int i = 0, j = 0, distance[(*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob], temp = 0, indice;

    for(i = 0; i < (*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob; i++)        // On test tout les mob de la salle actuelle
    {
        if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].statue == VIVANT)
            distance[i] = sqrt(pow((persox + persow/2) - ((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.x + (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.w/2), 2) + pow((persoy + persoh/2) - ((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.y + (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.h/2), 2));
        else
            distance[i] = 10000;
    }

    indice = 4;

    for(j = 4; j > 0; j--)
    {
        if(distance[j] < distance[j-1])
        {
            temp = distance[j];
            distance[j] = distance[j-1];
            distance[j-1] = temp;
        }
        else
            indice = j - 1;
    }

    if(distance[0] <= (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].rayon)
    {
        if((*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].durabilite > 0 || (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].munition > 0)
        {
            if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].pv > 0)
            {
                (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].pv -= (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].dmg;     
                printf("Poro a pris %d points de degats\n", (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].dmg);     
            }
   
            if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].pv <= 0 && (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].statue != MORT)
            {
                    (*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob_mort++;
                    (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].statue = MORT;
            }

            switch((*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].type)
            {
                case 'C':
                    (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].durabilite--;
                    break;

                case 'D':
                    (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].munition--;
                    break;

                default:
                    break;
            }
            return 1;


        }else
        {
            switch((*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].type)
            {
                case 'C':
                    printf("Plus de durabilité !\n");
                    break;

                case 'D':
                    printf("Plus de munition !\n");
                    break;

                default:
                    break;
            }
            return 0;
        }
    }
    return 0;
}

int test_clique_droit(jeu_t *jeu)
{
    int persox = (*jeu).perso.perso.x;
    int persoy = (*jeu).perso.perso.y;
    int persow = (*jeu).perso.perso.w;
    int persoh = (*jeu).perso.perso.h;

    int i = 0, j = 0, distance[(*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob], temp = 0, indice;

    for(i = 0; i < (*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob; i++)        // On test tout les mob de la salle actuelle
    {
        if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].statue == VIVANT)
            distance[i] = sqrt(pow((persox + persow/2) - ((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.x + (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.w/2), 2) + pow((persoy + persoh/2) - ((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.y + (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.h/2), 2));
        else
            distance[i] = 10000;
    }

    indice = 4;

    for(j = 4; j > 0; j--)
    {
        if(distance[j] < distance[j-1])
        {
            temp = distance[j];
            distance[j] = distance[j-1];
            distance[j-1] = temp;
        }
        else
            indice = j - 1;
    }

    if(distance[0] <= (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].rayon)
    {
        if((*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].durabilite > 0 || (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].munition > 0)
        {
            if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].pv > 0)
            {
                (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].pv -= (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].dmg*3;
                printf("Poro a pris %d points de degats\n", (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].dmg*3);      
            }       

            if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].pv <= 0 && (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].statue != MORT)
            {
                    (*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob_mort++;
                    (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].statue = MORT;
            }

            switch((*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].type)
            {
                case 0:
                    (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].durabilite -= 3;
                    break;

                case 1:
                    (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].munition -= 3;
                    break;

                default:
                    break;
            }
            return 1;


        }else
        {
            printf("Plus de munition !\n");
            return 0;
        }
    }
    return 0;
}


