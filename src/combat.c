#include "combat.h"

/**
 * \brief Gestion des clics pour le combat
 * \file 'combat.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief Attaque normal (corps à corps ou distance en fonction de l'arme)
 * 
 * @param jeu Chargement de la partie en cours
 * @return int On retourne si oui où non sa touche
 */

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
                DEBUG_MODE
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
                    DEBUG_MODE
                        printf("Plus de durabilité !\n");
                    break;

                case 'D':
                    DEBUG_MODE
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

/**
 * @brief Attaque chargé (rafale ou dégats de zones en fonction de l'arme)
 * 
 * @param jeu Chargement de la partie en cours
 * @return int On retourne si oui où non sa touche
 */

int test_clique_droit(jeu_t *jeu)
{
    int persox = (*jeu).perso.perso.x;
    int persoy = (*jeu).perso.perso.y;
    int persow = (*jeu).perso.perso.w;
    int persoh = (*jeu).perso.perso.h;

    int i = 0, j = 0, distance[(*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob], temp = 0, indice, tir = 0;

    /*
            On calcul la distance entre les mob et le personnage, et on les range dans un tableau, si le mob est MORT, alors la distance est 10000
    */

    for(i = 0; i < (*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob; i++)        // On test tout les mob de la salle actuelle
    {
        if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].statue == VIVANT)
            distance[i] = sqrt(pow((persox + persow/2) - ((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.x + (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.w/2), 2) + pow((persoy + persoh/2) - ((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.y + (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[i].mob.h/2), 2));
        else
            distance[i] = 10000;
    }

    indice = 4;

    /*
            Si l'arme est de type DISTANCE, alors on fait un tir en chaine
    */

    if((*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].type == 'D')
    {
        DEBUG_MODE
            printf("Arme DIST clic-droit\n");

        /*
                On trie la plus petite distance au niveau du tableau[0]
        */

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

        /*
                On prend le mob le plus proche, et si la distance entre le mob et le perosnnage est inférieur au rayon de l'arme actuelle, on lui inflige des dégats
        */

        if(distance[0] <= (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].rayon)
        {

            /*
                    on test si l'arme à des munition, si oui on tire sur le mob sinon non
            */

            if((*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].munition > 0)
            {

                /*
                        Si le mod visé à plus de 0 pv, alors on lui tir dessus
                */

                if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].pv > 0)
                {
                    (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].pv -= (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].dmg*3;
                    DEBUG_MODE
                        printf("Poro a pris %d points de degats\n", (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].dmg*3);
                }

                /*
                        Si le mob à 0 ou moins pv, et qu'il a un statue VIVANT, alors on lui donne le status MORT
                */

                if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].pv <= 0 && (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].statue != MORT)
                {
                        (*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob_mort++;
                        (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[indice].statue = MORT;
                }

                /*
                        On enlève 3 munition à l'arme
                */

                (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].munition -= 3;

                return 1;

            }else
            {
                DEBUG_MODE
                    printf("Plus de munition !\n");
                return 0;
            }
        }

    /*
        On test si l'arme estd e type CAC, si oui on fait des dégâts de zone
    */

    }else if((*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].type == 'C'){

        DEBUG_MODE
            printf("Arme CAC clic-droit\n");
        /*
                On test les distances entre le mob en question et le personnage
        */

        for(j = 0; j < (*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob; j++)
        {

            /*
                    On test si la distance entre le mob et le personnage est inférieur au rayon de l'arme, si oui alors on lui inflige des dégats
            */

            if(distance[j] <= (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].rayon)
            {
                /*
                        Si l'arme a de la durabilité, alors on peut taper l'ennemi
                */

                if((*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].durabilite > 0)
                {

                    /*
                            Si le mod visé à plus de 0 pv, alors on lui tir dessus
                    */

                    if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[j].pv > 0)
                    {
                        (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[j].pv -= (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].dmg*3;
                        DEBUG_MODE
                            printf("Poro a pris %d points de degats\n", (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].dmg*3);
                    }

                    /*
                            Si le mob à 0 ou moins pv, et qu'il a un statue VIVANT, alors on lui donne le status MORT
                    */

                    if((*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[j].pv <= 0 && (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[j].statue != MORT)
                    {
                            (*jeu).lab.tab_salle[(*jeu).perso.tag].nb_mob_mort++;
                            (*jeu).lab.tab_salle[(*jeu).perso.tag].tab_mob[j].statue = MORT;
                    }

                    /*
                            On enlève 3 durabilité à l'arme
                    */

                    (*jeu).perso.tab_arme[(*jeu).perso.arme_actuelle].durabilite -= 3;


                }else
                {
                    DEBUG_MODE
                        printf("Plus de durabilité !\n");
                    tir++;
                }
            }
        }
        if(tir != 5)
            return 1;
        else return 0;
    }
    return 0;
}


