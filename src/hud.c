#include "hud.h"

/**
 * \brief Fichier qui influe sur les salles du programme
 * \file 'hud.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief Initialisation des coordonnées du HUD avec la barre de vie et les items selectionner
 * 
 * @param jeu       C'est la structure contenant toute les données de la partie en question
 * @return jeu_t    On return la partie en question
 */

jeu_t init_hud(jeu_t *jeu)
{
    // Création du rectangle barre de vie

    (*jeu).hud.barre_pv.x = 40;
    (*jeu).hud.barre_pv.y = 40;
    (*jeu).hud.barre_pv.w = 200;
    (*jeu).hud.barre_pv.h = 40;

    // Création du rectangle objet Dist

    (*jeu).hud.item_dist.x = 280;
    (*jeu).hud.item_dist.y = 40;
    (*jeu).hud.item_dist.w = 40;
    (*jeu).hud.item_dist.h = 40;

    // Création du rectangle objet Cac

    (*jeu).hud.item_cac.x = 340;
    (*jeu).hud.item_cac.y = 40;
    (*jeu).hud.item_cac.w = 40;
    (*jeu).hud.item_cac.h = 40;

    return *jeu;
}

jeu_t init_texture_hud(jeu_t *jeu)
{
    (*jeu).hud.img_pv[0] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_1.bmp");
    (*jeu).hud.img_pv[1] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_2.bmp");
    (*jeu).hud.img_pv[2] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_3.bmp");
    (*jeu).hud.img_pv[3] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_4.bmp");
    (*jeu).hud.img_pv[4] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_5.bmp");
    (*jeu).hud.img_pv[5] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_6.bmp");
    (*jeu).hud.img_pv[6] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_7.bmp");
    (*jeu).hud.img_pv[7] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_8.bmp");
    (*jeu).hud.img_pv[8] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_9.bmp");
    (*jeu).hud.img_pv[9] = SDL_LoadBMP("../src/img/template_pv/pv_joueur_10.bmp");
    return *jeu;
}

/**
 * @brief Sert à afficher l'interface utilisateur, sur le rendu en paramètre
 * 
 *
 * 
 * @param renderer  C'est le Rendu d'acquisition
 * @param jeu       C'est la structure contenant toute les données de la partie en question
 */

void affichage_hud(SDL_Renderer *renderer, jeu_t *jeu)
{
    SDL_Texture *texture = NULL;

    int i = 0;

    for(i = 0; i<10; i++)
    {
        if((*jeu).hud.img_pv[i] == NULL){
            clean_ressources(NULL, renderer, texture);
            SDL_ExitWithError("Impossible de charger l'image x10");
        }
    }

    SDL_SetColorKey((*jeu).hud.img_pv[(*jeu).perso.pv-1], SDL_TRUE, SDL_MapRGB((*jeu).hud.img_pv[(*jeu).perso.pv-1]->format, 30, 6, 236));

    texture = SDL_CreateTextureFromSurface(renderer, (*jeu).hud.img_pv[(*jeu).perso.pv-1]);

    if(texture == NULL){
        clean_ressources(NULL, renderer, texture);
        SDL_ExitWithError("Impossible de créer la texture");
    }

    if(SDL_QueryTexture(texture, NULL, NULL, &(*jeu).hud.barre_pv.w, &(*jeu).hud.barre_pv.h) != 0){
        clean_ressources(NULL, renderer, texture);
        SDL_ExitWithError("Impossible de créer la texture");
    }

    if(SDL_RenderCopy(renderer, texture, NULL, &(*jeu).hud.barre_pv) != 0){
        clean_ressources(NULL, renderer, texture);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }
    SDL_DestroyTexture(texture);

    if((*jeu).perso.arme_actuelle == 0)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &(*jeu).hud.item_dist);
    }else if((*jeu).perso.arme_actuelle == 1)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &(*jeu).hud.item_cac);
    }
}

void ouvrir_inventaire(SDL_Renderer *renderer, SDL_Window *fen, jeu_t *jeu, SDL_bool plein_ecran)
{
    SDL_Event event;
    SDL_bool dans_inventaire = SDL_TRUE;
    int k = 0, num_case = 0, i = 0;

    (*jeu).perso.inv.cases[0].item_actuel = 10;

    afficher_texture(renderer, fen, (*jeu).perso.inv.texture_inventaire, (*jeu).perso.inv.pos_inventaire, plein_ecran, 50, 20, -1, -1);

    for(int i = 0, posY = 28; i < 3; i++, posY += 12)
    {
        for(int j = 0, posX = 43; j < 3; j++, posX += 7, k++)
        {
            (*jeu).perso.inv.cases[k].pos_case = afficher_texture(renderer, fen, (*jeu).perso.inv.texture_case, (*jeu).perso.inv.cases[k].pos_case, plein_ecran, posX, posY, -1, -1);
        }
    }

    afficher_texture(renderer, fen, (*jeu).perso.inv.texture_inventaire_armes, (*jeu).perso.inv.pos_inventaire_armes, plein_ecran, 50, 95, -1, -1);

    (*jeu).perso.inv.cases[10].pos_case = afficher_texture(renderer, fen, (*jeu).perso.inv.texture_case, (*jeu).perso.inv.cases[10].pos_case, plein_ecran, 45, 93, -1, -1);
    (*jeu).perso.inv.cases[11].pos_case = afficher_texture(renderer, fen, (*jeu).perso.inv.texture_case, (*jeu).perso.inv.cases[11].pos_case, plein_ecran, 55, 93, -1, -1);

    SDL_RenderPresent(renderer);
    
    while(dans_inventaire)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_i:
                        case SDLK_ESCAPE:
                            dans_inventaire = SDL_FALSE;
                            break;

                        default:
                            break;
                    }
                case SDL_MOUSEBUTTONDOWN:
                    num_case = position_inventaire(jeu, event);
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        if(num_case != -1)
                            printf("Case n°%d\n", num_case);

                    }else if(event.button.button == SDL_BUTTON_RIGHT)
                    {
                        for(i = 0; i<9; i++)
                        {
                            if(num_case == (*jeu).perso.inv.cases[i].item_actuel)
                            {
                                if((*jeu).perso.inv.loot.potion[0].nb_potion > 0 && (*jeu).perso.pv != 10)
                                {
                                    (*jeu).perso.inv.loot.potion[0].nb_potion--;
                                    (*jeu).perso.pv = 10;
                                }
                            }
                        }
                    }
                    break;

                default:
                    break;

            }
        }
    }
}


int position_inventaire(jeu_t *jeu, SDL_Event event)
{
    if(event.motion.x > (*jeu).perso.inv.cases[0].pos_case.x && event.motion.x < ((*jeu).perso.inv.cases[0].pos_case.x + (*jeu).perso.inv.cases[0].pos_case.w))
    {
        if(event.motion.y > (*jeu).perso.inv.cases[0].pos_case.y && event.motion.y < ((*jeu).perso.inv.cases[0].pos_case.y + (*jeu).perso.inv.cases[0].pos_case.h))
        {
            return(1);
        }
    }

    if(event.motion.x > (*jeu).perso.inv.cases[1].pos_case.x && event.motion.x < ((*jeu).perso.inv.cases[1].pos_case.x + (*jeu).perso.inv.cases[1].pos_case.w))
    {
        if(event.motion.y > (*jeu).perso.inv.cases[1].pos_case.y && event.motion.y < ((*jeu).perso.inv.cases[1].pos_case.y + (*jeu).perso.inv.cases[1].pos_case.h))
        {
            return(2);
        }
    }

    if(event.motion.x > (*jeu).perso.inv.cases[2].pos_case.x && event.motion.x < ((*jeu).perso.inv.cases[2].pos_case.x + (*jeu).perso.inv.cases[2].pos_case.w))
    {
        if(event.motion.y > (*jeu).perso.inv.cases[2].pos_case.y && event.motion.y < ((*jeu).perso.inv.cases[2].pos_case.y + (*jeu).perso.inv.cases[2].pos_case.h))
        {
            return(3);
        }
    }

    if(event.motion.x > (*jeu).perso.inv.cases[3].pos_case.x && event.motion.x < ((*jeu).perso.inv.cases[3].pos_case.x + (*jeu).perso.inv.cases[3].pos_case.w))
    {
        if(event.motion.y > (*jeu).perso.inv.cases[3].pos_case.y && event.motion.y < ((*jeu).perso.inv.cases[3].pos_case.y + (*jeu).perso.inv.cases[3].pos_case.h))
        {
            return(4);
        }
    }

    if(event.motion.x > (*jeu).perso.inv.cases[4].pos_case.x && event.motion.x < ((*jeu).perso.inv.cases[4].pos_case.x + (*jeu).perso.inv.cases[4].pos_case.w))
    {
        if(event.motion.y > (*jeu).perso.inv.cases[4].pos_case.y && event.motion.y < ((*jeu).perso.inv.cases[4].pos_case.y + (*jeu).perso.inv.cases[4].pos_case.h))
        {
            return(5);
        }
    }

    if(event.motion.x > (*jeu).perso.inv.cases[5].pos_case.x && event.motion.x < ((*jeu).perso.inv.cases[5].pos_case.x + (*jeu).perso.inv.cases[5].pos_case.w))
    {
        if(event.motion.y > (*jeu).perso.inv.cases[5].pos_case.y && event.motion.y < ((*jeu).perso.inv.cases[5].pos_case.y + (*jeu).perso.inv.cases[5].pos_case.h))
        {
            return(6);
        }
    }

    if(event.motion.x > (*jeu).perso.inv.cases[6].pos_case.x && event.motion.x < ((*jeu).perso.inv.cases[6].pos_case.x + (*jeu).perso.inv.cases[6].pos_case.w))
    {
        if(event.motion.y > (*jeu).perso.inv.cases[6].pos_case.y && event.motion.y < ((*jeu).perso.inv.cases[6].pos_case.y + (*jeu).perso.inv.cases[6].pos_case.h))
        {
            return(7);
        }
    }

    if(event.motion.x > (*jeu).perso.inv.cases[7].pos_case.x && event.motion.x < ((*jeu).perso.inv.cases[7].pos_case.x + (*jeu).perso.inv.cases[7].pos_case.w))
    {
        if(event.motion.y > (*jeu).perso.inv.cases[7].pos_case.y && event.motion.y < ((*jeu).perso.inv.cases[7].pos_case.y + (*jeu).perso.inv.cases[7].pos_case.h))
        {
            return(8);
        }
    }

    if(event.motion.x > (*jeu).perso.inv.cases[8].pos_case.x && event.motion.x < ((*jeu).perso.inv.cases[8].pos_case.x + (*jeu).perso.inv.cases[8].pos_case.w))
    {
        if(event.motion.y > (*jeu).perso.inv.cases[8].pos_case.y && event.motion.y < ((*jeu).perso.inv.cases[8].pos_case.y + (*jeu).perso.inv.cases[8].pos_case.h))
        {
            return(9);
        }
    }
    return(-1);
}

int chercher_case(jeu_t *jeu)
{
    int i = 0;
    for(i = 0; i<11; i++)
    {
        //if((*jeu).perso.inv.cases[i].item_actuel == (*jeu).perso.inv.loot.potion[]
    }
}