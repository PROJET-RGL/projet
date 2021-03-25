#include "menu.h"

/**
 * \brief Fichier contenant les fonctions chargeant le menu et ses images
 * \file 'menu.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 mars 2021
 */

/**
 * @brief Chargement et affichage du menu
 * 
 * @param renderer Attributs pour l'affiche d'une fenêtre
 * @param fen Fenêtre sur laquelle on veut afficher les options
 * @param menu Tableau contenant les textures du menu
 * @param options Tableau contenant les textures des options
 * @param commandes Tableau contenant les textures des commandes
 * @param volume Volume actuel de la musique
 * @param charge Indique si un partie a déjà été lancée
 * @param jeu Chargement de la partie en cours
 * @param plein_ecran Indique si le jeu est en plein écran
 * @param program_launched État actuel du jeu
 * @param en_partie Indique si une partie est déjà en cours
 * @return SDL_bool - Retourne si l'utilisateur souhaite quitter ou non le jeu
 */

SDL_bool load_menu(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *menu[7], SDL_Texture *options[10], SDL_Texture *commandes[10], int *volume, SDL_bool *charge, jeu_t *jeu, SDL_bool *plein_ecran, SDL_bool *program_launched, SDL_bool en_partie)
{
    SDL_Event event;
    SDL_bool quitter_jeu = SDL_TRUE, att_menu = SDL_TRUE, chargement = SDL_FALSE;
    int opt = 0;

    nettoyage_ecran(renderer);

    pos_menu[0] = afficher_texture(renderer, fen, menu[0], pos_menu[0], *plein_ecran, 50, 10);

    if(!en_partie)
        pos_menu[1] = afficher_texture(renderer, fen, menu[1], pos_menu[1], *plein_ecran, 50, 50);
    else
        pos_menu[1] = afficher_texture(renderer, fen, menu[2], pos_menu[1], *plein_ecran, 50, 50);

    pos_menu[3] = afficher_texture(renderer, fen, menu[3], pos_menu[3], *plein_ecran, 50, 70);

    if(!en_partie)
        pos_menu[4] = afficher_texture(renderer, fen, menu[4], pos_menu[4], *plein_ecran, 50, 90);
    else
        pos_menu[4] = afficher_texture(renderer, fen, menu[5], pos_menu[4], *plein_ecran, 50, 90);

    SDL_RenderPresent(renderer);

    while(att_menu != SDL_FALSE)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT :
                    att_menu = SDL_FALSE;
                    quitter_jeu = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONUP :
                    if(chargement == SDL_FALSE)
                    {
                        if(event.motion.x > pos_menu[1].x && event.motion.x < (pos_menu[1].x + pos_menu[1].w))
                        {
                            if(event.motion.y > pos_menu[4].y && event.motion.y < (pos_menu[4].y + pos_menu[4].h))
                            {
                                    att_menu = SDL_FALSE;
                                    quitter_jeu = SDL_FALSE;
                                    if(en_partie)
                                       sauvegarde(jeu);
                            }
                            if(event.motion.y > pos_menu[1].y && event.motion.y < (pos_menu[1].y + pos_menu[1].h))
                            {
                                if(!en_partie)
                                {
                                    chargement = SDL_TRUE;
                                    nettoyage_ecran(renderer);
                                    pos_menu[0] = afficher_texture(renderer, fen, menu[0], pos_menu[0], *plein_ecran, 50, 10);
                                    pos_menu[6] = afficher_texture(renderer, fen, menu[6], pos_menu[6], *plein_ecran, 50, 50);
                                    pos_menu[7] = afficher_texture(renderer, fen, menu[7], pos_menu[7], *plein_ecran, 50, 70);
                                    pos_menu[8] = afficher_texture(renderer, fen, menu[8], pos_menu[8], *plein_ecran, 50, 90);

                                    SDL_RenderPresent(renderer);
                                }
                                else
                                {
                                    att_menu = SDL_FALSE;
                                }

                            }
                            if(event.motion.y > pos_menu[3].y && event.motion.y < (pos_menu[3].y + pos_menu[3].h))
                            {
                                opt = 1;
                            }
                        }
                    }
                    else
                    {

                        if(event.motion.x > pos_menu[6].x && event.motion.x < (pos_menu[6].x + pos_menu[6].w))
                        {
                            if(event.motion.y > pos_menu[6].y && event.motion.y < (pos_menu[6].y + pos_menu[6].h))
                            {
                                *charge = SDL_FALSE;
                                att_menu = SDL_FALSE;
                            }
                        }
                        if(event.motion.x > pos_menu[7].x && event.motion.x < (pos_menu[7].x + pos_menu[7].w))
                        {
                            if(event.motion.y > pos_menu[7].y && event.motion.y < (pos_menu[7].y + pos_menu[7].h))
                            {
                                *charge = SDL_TRUE;
                                att_menu = SDL_FALSE;
                            }
                        }
                        if(event.motion.x > pos_menu[8].x && event.motion.x < (pos_menu[8].x + pos_menu[8].w))
                        {
                            if(event.motion.y > pos_menu[8].y && event.motion.y < (pos_menu[8].y + pos_menu[8].h))
                            {
                                chargement = SDL_FALSE;
                                nettoyage_ecran(renderer);
                                reload_img(renderer, fen, menu, options, commandes, volume, *plein_ecran, -1);

                            }
                        }
                    }
                    break;

                default :
                    break;
            }
        }
        if(opt == 1)
        {
            nettoyage_ecran(renderer);

            *program_launched = load_option(renderer, fen, options, commandes, volume, plein_ecran);
            if(*program_launched == SDL_FALSE)
            {
                att_menu = SDL_FALSE;
                quitter_jeu = SDL_FALSE;
            }
            else
            {
                opt = 0;
                nettoyage_ecran(renderer);

                pos_menu[0] = afficher_texture(renderer, fen, menu[0], pos_menu[0], *plein_ecran, 50, 10);

                if(!en_partie)
                    pos_menu[1] = afficher_texture(renderer, fen, menu[1], pos_menu[1], *plein_ecran, 50, 50);
                else
                    pos_menu[1] = afficher_texture(renderer, fen, menu[2], pos_menu[1], *plein_ecran, 50, 50);

                pos_menu[3] = afficher_texture(renderer, fen, menu[3], pos_menu[3], *plein_ecran, 50, 70);

                if(!en_partie)
                    pos_menu[4] = afficher_texture(renderer, fen, menu[4], pos_menu[4], *plein_ecran, 50, 90);
                else
                    pos_menu[4] = afficher_texture(renderer, fen, menu[5], pos_menu[4], *plein_ecran, 50, 90);

                SDL_RenderPresent(renderer);
            }
                
        }
    }

    return quitter_jeu;
}

/**
 * @brief Chargement et affichage des options
 * 
 * @param renderer Attributs pour l'affiche d'une fenêtre
 * @param fen Fenêtre sur laquelle on veut afficher les options
 * @param options Tableau contenant les textures des options
 * @param commandes Tableau contenant les textures des commandes
 * @param volume Volume actuel de la musique
 * @param plein_ecran Indique si le jeu est en plein écran
 * @return SDL_bool Retourne si l'utilisateur souhaite quitter le jeu
 */

SDL_bool load_option(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *options[10], SDL_Texture *commandes[10], int *volume, SDL_bool *plein_ecran)
{

    SDL_Event event;
    SDL_bool att_option = SDL_TRUE;
    SDL_bool quitter_jeu = SDL_TRUE;
    int i, pX, choix = 1;

    pos_options[0] = afficher_texture(renderer, fen, options[0], pos_options[0], *plein_ecran, 35, 5);
    pos_options[1] = afficher_texture(renderer, fen, options[1], pos_options[1], *plein_ecran, 75, 5);
    pos_options[2] = afficher_texture(renderer, fen, options[2], pos_options[2], *plein_ecran, 5, 5);
    pos_options[3] = afficher_texture(renderer, fen, options[3], pos_options[3], *plein_ecran, 35, 35);
    pos_options[4] = afficher_texture(renderer, fen, options[4], pos_options[4], *plein_ecran, 65, 35);
    pos_options[5] = afficher_texture(renderer, fen, options[5], pos_options[5], *plein_ecran, 33, 55);
    pos_options[6] = afficher_texture(renderer, fen, options[6], pos_options[6], *plein_ecran, 43, 55);
    pos_options[7] = afficher_texture(renderer, fen, options[7], pos_options[7], *plein_ecran, 67, 55);

    for(i = 0, pX = 46; i < 100; i += 10, pX += 2)
    {
        if(i < *volume)
            pos_options[8] = afficher_texture(renderer, fen, options[8], pos_options[8], *plein_ecran, pX, 55); 
        else
            pos_options[9] = afficher_texture(renderer, fen, options[9], pos_options[9], *plein_ecran, pX, 55);
    }

    SDL_RenderPresent(renderer);

    while(att_option != SDL_FALSE)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT :
                    att_option = SDL_FALSE;
                    quitter_jeu = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONUP :
                    if(event.motion.x > pos_options[0].x && event.motion.x < (pos_options[0].x + pos_options[0].w))
                    {
                        if(event.motion.y > pos_options[0].y && event.motion.y < (pos_options[0].y + pos_options[0].h)){
                            choix = 1;
                            nettoyage_ecran(renderer);
                            reload_img(renderer, fen, NULL, options, commandes, volume, *plein_ecran, choix);
                        }
                    }

                    if(event.motion.x > pos_options[1].x && event.motion.x < (pos_options[1].x + pos_options[1].w))
                    {
                        if(event.motion.y > pos_options[1].y && event.motion.y < (pos_options[1].y + pos_options[1].h)){
                            choix = 2;
                            nettoyage_ecran(renderer);
                            reload_img(renderer, fen, NULL, options, commandes, volume, *plein_ecran, choix);                        }
                    }

                    if(event.motion.x > pos_options[2].x && event.motion.x < (pos_options[2].x + pos_options[2].w))
                    {
                        if(event.motion.y > pos_options[2].y && event.motion.y < (pos_options[2].y + pos_options[2].h))
                            att_option = SDL_FALSE;
                    }

                    if(choix == 1)
                    {
                        if(event.motion.x > pos_options[3].x && event.motion.x < (pos_options[3].x + pos_options[3].w))
                        {
                            if(event.motion.y > pos_options[3].y && event.motion.y < (pos_options[3].y + pos_options[3].h)){
                                *plein_ecran = 1;
                                SDL_SetWindowPosition(fen, 0, 0);
                                SDL_SetWindowSize(fen, 1920, 1080);
                                SDL_SetWindowBordered(fen, SDL_FALSE);
                                nettoyage_ecran(renderer);
                                reload_img(renderer, fen, NULL, options, commandes, volume, *plein_ecran, choix);
                            }
                        }

                        if(event.motion.x > pos_options[4].x && event.motion.x < (pos_options[4].x + pos_options[4].w))
                        {
                            if(event.motion.y > pos_options[4].y && event.motion.y < (pos_options[4].y + pos_options[4].h)){
                                *plein_ecran = 0;
                                SDL_SetWindowPosition(fen, (1920 - FEN_LARGEUR)/2, (1080 - FEN_HAUTEUR)/2);
                                SDL_SetWindowSize(fen, 1440, 900);
                                SDL_SetWindowBordered(fen, SDL_TRUE);
                                nettoyage_ecran(renderer);
                                reload_img(renderer, fen, NULL, options, commandes, volume, *plein_ecran, choix);
                            }
                        }

                        if(event.motion.x > pos_options[6].x && event.motion.x < (pos_options[6].x + pos_options[6].w))
                        {
                            if(event.motion.y > pos_options[6].y && event.motion.y < (pos_options[6].y + pos_options[6].h)){
                                if(*volume != 0){
                                    *volume -= 10;
                                    Mix_VolumeMusic(*volume);
                                    nettoyage_ecran(renderer);
                                    reload_img(renderer, fen, NULL, options, commandes, volume, *plein_ecran, choix);
                                }
                            }
                        }

                        if(event.motion.x > pos_options[7].x + 20 && event.motion.x < (pos_options[7].x + pos_options[7].w))
                        {
                            if(event.motion.y > pos_options[7].y && event.motion.y < (pos_options[7].y + pos_options[7].h)){
                                if(*volume != 100){
                                    *volume += 10;
                                    Mix_VolumeMusic(*volume);
                                    nettoyage_ecran(renderer);
                                    reload_img(renderer, fen, NULL, options, commandes, volume, *plein_ecran, choix);
                                }
                            }
                        }
                    }
                    
                    break;
                default :
                    break;
            }
        }
    }

    nettoyage_ecran(renderer);
    
    return quitter_jeu;
}

/**
 * @brief Rechargement des images
 * 
 * @param renderer Attributs pour l'affiche d'une fenêtre
 * @param fen Fenêtre sur laquelle on veut afficher les options
 * @param menu Tableau contenant les textures du menu
 * @param options Tableau contenant les textures des options
 * @param commandes Tableau contenant les textures des commandes
 * @param volume Volume actuel de la musique
 * @param plein_ecran Indique si le jeu est en plein écran
 * @param choix Choix des images à recharger (1 = charger les options général, 2 = charger la liste des commandes)
 * @return void
 */

void reload_img(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *menu[7], SDL_Texture *options[10], SDL_Texture *commandes[10], int *volume, SDL_bool plein_ecran, int choix)
{
    int i;
    int pX = 46;

    if(choix != -1)
    {
        pos_options[0] = afficher_texture(renderer, fen, options[0], pos_options[0], plein_ecran, 35, 5);
        pos_options[1] = afficher_texture(renderer, fen, options[1], pos_options[1], plein_ecran, 75, 5);
        pos_options[2] = afficher_texture(renderer, fen, options[2], pos_options[2], plein_ecran, 5, 5);

        if(choix == 1)
        {
            pos_options[3] = afficher_texture(renderer, fen, options[3], pos_options[3], plein_ecran, 35, 35);
            pos_options[4] = afficher_texture(renderer, fen, options[4], pos_options[4], plein_ecran, 65, 35);
            pos_options[5] = afficher_texture(renderer, fen, options[5], pos_options[5], plein_ecran, 33, 55);
            pos_options[6] = afficher_texture(renderer, fen, options[6], pos_options[6], plein_ecran, 43, 55);
            pos_options[7] = afficher_texture(renderer, fen, options[7], pos_options[7], plein_ecran, 67, 55);

            for(i = 0, pX = 46; i < 100; i += 10, pX += 2)
            {
                if(i < *volume)
                    pos_options[8] = afficher_texture(renderer, fen, options[8], pos_options[8], plein_ecran, pX, 55); 
                else
                    pos_options[9] = afficher_texture(renderer, fen, options[9], pos_options[9], plein_ecran, pX, 55);
            }
        }

        if(choix == 2)
        {
            afficher_texture(renderer, fen, commandes[0], pos_commandes[0], plein_ecran, 35, 30);
            afficher_texture(renderer, fen, commandes[1], pos_commandes[1], plein_ecran, 35, 40);
            afficher_texture(renderer, fen, commandes[2], pos_commandes[2], plein_ecran, 35, 50);
            afficher_texture(renderer, fen, commandes[3], pos_commandes[3], plein_ecran, 35, 60);
            afficher_texture(renderer, fen, commandes[4], pos_commandes[4], plein_ecran, 65, 30);
            afficher_texture(renderer, fen, commandes[5], pos_commandes[5], plein_ecran, 65, 40);
            afficher_texture(renderer, fen, commandes[6], pos_commandes[6], plein_ecran, 65, 50);
            afficher_texture(renderer, fen, commandes[7], pos_commandes[7], plein_ecran, 65, 60);
        }
    }
    else
    {
        pos_menu[0] = afficher_texture(renderer, fen, menu[0], pos_menu[0], plein_ecran, 50, 10);
        pos_menu[1] = afficher_texture(renderer, fen, menu[1], pos_menu[1], plein_ecran, 50, 50);
        pos_menu[3] = afficher_texture(renderer, fen, menu[3], pos_menu[3], plein_ecran, 50, 70);
        pos_menu[4] = afficher_texture(renderer, fen, menu[4], pos_menu[4], plein_ecran, 50, 90);
    }

    SDL_RenderPresent(renderer);
}