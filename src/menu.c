#include "menu.h"

/**
 * \brief Fichier contenant les fonctions chargeant le menu et ses images
 * \file 'menu.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 18 Février 2020
 */

/**
 * @brief Chargement et affichage du menu
 * 
 * @param renderer Attributs pour l'affiche d'une fenêtre
 * @param fen Fenêtre sur laquelle on veut afficher les options
 * @param volume Volume actuel de la musique
 * @param plein_ecran Indique si le jeu est en plein écran
 * @param ingame Indique si un partie a déjà été lancée
 * @return int - Retourne si l'utilisateur souhaite quitter ou non le jeu
 */

int load_menu(SDL_Renderer *renderer, SDL_Window *fen, int *volume, SDL_bool *plein_ecran, SDL_bool ingame, SDL_bool *charge, jeu_t *jeu){

    SDL_Event event;
    SDL_bool program_lunched = SDL_TRUE;
    SDL_bool att_menu = SDL_TRUE;
    SDL_bool chargement = SDL_FALSE;
    int opt = 0;

    nettoyage_ecran(renderer);
    logo = load_img(renderer, fen, "../src/img/logo.bmp", 50, 10, logo, plein_ecran);

    if(!ingame)
        start = load_img(renderer, fen, "../src/img/jouer.bmp", 50, 50, start, plein_ecran);
    else
        start = load_img(renderer, fen, "../src/img/continuer.bmp", 50, 50, start, plein_ecran);

    option = load_img(renderer, fen, "../src/img/options.bmp", 50, 70, option, plein_ecran);

    if(!ingame)
        quit = load_img(renderer, fen, "../src/img/quitter.bmp", 50, 90, quit, plein_ecran);
    else
        quit = load_img(renderer, fen, "../src/img/sauv_quitter.bmp", 50, 90, quit, plein_ecran);

    while(att_menu != SDL_FALSE)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT :
                    att_menu = SDL_FALSE;
                    program_lunched = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONUP :
                    if(chargement == SDL_FALSE)
                    {
                        if(event.motion.x > quit.x && event.motion.x < (quit.x + quit.w))
                        {
                            if(event.motion.y > quit.y && event.motion.y < (quit.y + quit.h))
                            {
                                    att_menu = SDL_FALSE;
                                    program_lunched = SDL_FALSE;
                                    if(ingame)
                                       sauvegarde(jeu);
                            }
                            if(event.motion.y > start.y && event.motion.y < (start.y + start.h))
                            {
                                if(!ingame)
                                {
                                    chargement = SDL_TRUE;
                                    nettoyage_ecran(renderer);
                                    logo = load_img(renderer, fen, "../src/img/logo.bmp", 50, 10, logo, plein_ecran);
                                    nouvelle = load_img(renderer, fen, "../src/img/nouvelle.bmp", 50, 50, nouvelle, plein_ecran);
                                    charger = load_img(renderer, fen, "../src/img/charger.bmp", 50, 70, charger, plein_ecran);
                                    retour = load_img(renderer, fen, "../src/img/retour.bmp", 50, 90, retour, plein_ecran);
                                }
                                else
                                {
                                    att_menu = SDL_FALSE;
                                }

                            }
                            if(event.motion.y > option.y && event.motion.y < (option.y + option.h))
                            {
                                opt = 1;
                            }
                        }
                    }
                    else
                    {

                        if(event.motion.x > nouvelle.x && event.motion.x < (nouvelle.x + nouvelle.w))
                        {
                            if(event.motion.y > nouvelle.y && event.motion.y < (nouvelle.y + nouvelle.h))
                            {
                                att_menu = SDL_FALSE;
                            }
                        }
                        if(event.motion.x > charger.x && event.motion.x < (charger.x + charger.w))
                        {
                            if(event.motion.y > charger.y && event.motion.y < (charger.y + charger.h))
                            {
                                *charge = SDL_TRUE;
                                att_menu = SDL_FALSE;
                            }
                        }
                        if(event.motion.x > retour.x && event.motion.x < (retour.x + retour.w))
                        {
                            if(event.motion.y > retour.y && event.motion.y < (retour.y + retour.h))
                            {
                                chargement = SDL_FALSE;
                                nettoyage_ecran(renderer);
                                reload_img(renderer, fen, volume, plein_ecran, -1);
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
            load_option(renderer, fen, volume, plein_ecran);
            opt = 0;
            nettoyage_ecran(renderer);
            logo = load_img(renderer, fen, "../src/img/logo.bmp", 50, 10, logo, plein_ecran);

            if(!ingame)
                start = load_img(renderer, fen, "../src/img/jouer.bmp", 50, 50, start, plein_ecran);
            else
                start = load_img(renderer, fen, "../src/img/continuer.bmp", 50, 50, start, plein_ecran);

            option = load_img(renderer, fen, "../src/img/options.bmp", 50, 70, option, plein_ecran);
            if(!ingame)
                quit = load_img(renderer, fen, "../src/img/quitter.bmp", 50, 90, quit, plein_ecran);
            else
                quit = load_img(renderer, fen, "../src/img/sauv_quitter.bmp", 50, 90, quit, plein_ecran);
        }
    }
    return program_lunched;
}

/**
 * @brief Chargement et affichage des options
 * 
 * @param renderer Attributs pour l'affiche d'une fenêtre
 * @param fen Fenêtre sur laquelle on veut afficher les options
 * @param volume Volume actuel de la musique
 * @param plein_ecran Indique si le jeu est en plein écran
 * @param choix Choix des images à recharger (1 = charger les options général, 2 = charger la liste des commandes)
 * @return void
 */

void load_option(SDL_Renderer *renderer, SDL_Window *fen, int *volume, SDL_bool *plein_ecran)
{

    SDL_Event event;
    SDL_bool att_option = SDL_TRUE;
    int i, pX = 46, choix = 1;

    general = load_img(renderer, fen, "../src/img/general.bmp", 35, 5, general, plein_ecran);
    commandes = load_img(renderer, fen, "../src/img/commandes.bmp", 75, 5, commandes, plein_ecran);
    retour = load_img(renderer, fen, "../src/img/retour.bmp", 5, 5, retour, plein_ecran);
    fullscreen = load_img(renderer, fen, "../src/img/pleinecran.bmp", 35, 35, fullscreen, plein_ecran);
    classique = load_img(renderer, fen, "../src/img/fenetre.bmp", 65, 35, classique, plein_ecran);
    son = load_img(renderer, fen, "../src/img/son.bmp", 33, 55, son, plein_ecran);
    son_down = load_img(renderer, fen, "../src/img/son_down.bmp", 43, 55, son_down, plein_ecran);
    son_up = load_img(renderer, fen, "../src/img/son_up.bmp", 67, 55, son_up, plein_ecran);

    for(i = 0; i < 100; i += 10)
    {
        if(i < *volume)
        {
            son_barreup = load_img(renderer, fen, "../src/img/son_barreup.bmp", pX, 55, son_barreup, plein_ecran);
            pX += 2;
        }
        else
        {
            son_barredown = load_img(renderer, fen, "../src/img/son_barredown.bmp", pX, 55, son_barredown, plein_ecran);
            pX += 2;
        }
    }

    while(att_option != SDL_FALSE)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT :
                    att_option = SDL_FALSE;
                    SDL_bool program_lunched = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONUP :
                    if(event.motion.x > general.x && event.motion.x < (general.x + general.w))
                    {
                        if(event.motion.y > general.y && event.motion.y < (general.y + general.h)){
                            choix = 1;
                            nettoyage_ecran(renderer);
                            reload_img(renderer, fen, volume, plein_ecran, choix);
                        }
                    }

                    if(event.motion.x > commandes.x && event.motion.x < (commandes.x + commandes.w))
                    {
                        if(event.motion.y > commandes.y && event.motion.y < (commandes.y + commandes.h)){
                            choix = 2;
                            nettoyage_ecran(renderer);
                            reload_img(renderer, fen, volume, plein_ecran, choix);
                        }
                    }

                    if(event.motion.x > retour.x && event.motion.x < (retour.x + retour.w))
                    {
                        if(event.motion.y > retour.y && event.motion.y < (retour.y + retour.h))
                            att_option = SDL_FALSE;
                    }

                    if(choix == 1)
                    {
                        if(event.motion.x > fullscreen.x && event.motion.x < (fullscreen.x + fullscreen.w))
                        {
                            if(event.motion.y > fullscreen.y && event.motion.y < (fullscreen.y + fullscreen.h)){
                                *plein_ecran = 1;
                                SDL_SetWindowPosition(fen, 0, 0);
                                SDL_SetWindowSize(fen, 1920, 1080);
                                SDL_SetWindowBordered(fen, SDL_FALSE);
                                nettoyage_ecran(renderer);
                                reload_img(renderer, fen, volume, plein_ecran, choix);
                            }
                        }

                        if(event.motion.x > classique.x && event.motion.x < (classique.x + classique.w))
                        {
                            if(event.motion.y > classique.y && event.motion.y < (classique.y + classique.h)){
                                *plein_ecran = 0;
                                SDL_SetWindowPosition(fen, (1920 - FEN_LARGEUR)/2, (1080 - FEN_HAUTEUR)/2);
                                SDL_SetWindowSize(fen, 1440, 900);
                                SDL_SetWindowBordered(fen, SDL_TRUE);
                                nettoyage_ecran(renderer);
                                reload_img(renderer, fen, volume, plein_ecran, choix);
                            }
                        }

                        if(event.motion.x > son_down.x && event.motion.x < (son_down.x + son_down.w))
                        {
                            if(event.motion.y > son_down.y && event.motion.y < (son_down.y + son_down.h)){
                                if(*volume != 0){
                                    *volume -= 10;
                                    Mix_VolumeMusic(*volume);
                                    nettoyage_ecran(renderer);
                                    reload_img(renderer, fen, volume, plein_ecran, choix);
                                }
                            }
                        }

                        if(event.motion.x > son_up.x + 20 && event.motion.x < (son_up.x + son_up.w))
                        {
                            if(event.motion.y > son_up.y && event.motion.y < (son_up.y + son_up.h)){
                                if(*volume != 100){
                                    *volume += 10;
                                    Mix_VolumeMusic(*volume);
                                    nettoyage_ecran(renderer);
                                    reload_img(renderer, fen, volume, plein_ecran, choix);
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
}

/**
 * @brief Chargement et affichage des images
 * 
 * @param renderer Attributs pour l'affiche d'une fenêtre
 * @param fen Fenêtre sur laquelle on veut afficher les options
 * @param chemin_img Chemin relatif de l'image
 * @param pourcentX Position de la fenêtre en X en pourcentage
 * @param pourcentY Position de la fenêtre en Y en pourcentage
 * @param rect Indique quel rectangle utiliser pour l'image
 * @param volume Volume actuel de la musique
 * @param plein_ecran Indique si le jeu est en plein écran
 * @return SDL_Rect - Retourne des informations sur la position x, y des images ainsi que leurs tailles
 */

SDL_Rect load_img(SDL_Renderer *renderer, SDL_Window *fen, char *chemin_img, int pourcentX, int pourcentY, SDL_Rect rect, SDL_bool *plein_ecran)
{
    
    SDL_Texture *texture = NULL;
    SDL_Surface *img = NULL;
    
    img = SDL_LoadBMP(chemin_img);

    if(img == NULL){
        clean_ressources(fen, renderer, texture);
        SDL_ExitWithError("Impossible de charger l'image");
    }

    SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 30, 6, 236));

    texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    if(texture == NULL){
        clean_ressources(fen, renderer, texture);
        SDL_ExitWithError("Impossible de créer la texture");
    }

    if(SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) != 0){
        clean_ressources(fen, renderer, texture);
        SDL_ExitWithError("Impossible de créer la texture");
    }

    if(!*plein_ecran)
    {
        rect.x = ((FEN_LARGEUR - rect.w)*pourcentX)/100;
        rect.y = ((FEN_HAUTEUR - rect.h)*pourcentY)/100;
    }
    else
    {
        rect.x = ((1920 - rect.w)*pourcentX)/100;
        rect.y = ((1080 - rect.h)*pourcentY)/100;
    }
    
    if(SDL_RenderCopy(renderer, texture, NULL, &rect) != 0){
        clean_ressources(fen, renderer, texture);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
    return rect;
}

/**
 * @brief Rechargement des images des options
 * 
 * @param renderer Attributs pour l'affiche d'une fenêtre
 * @param fen Fenêtre sur laquelle on veut afficher les options
 * @param volume Volume actuel de la musique
 * @param plein_ecran Indique si le jeu est en plein écran
 * @param choix Choix des images à recharger (1 = charger les options général, 2 = charger la liste des commandes)
 * @return void
 */

void reload_img(SDL_Renderer *renderer, SDL_Window *fen, int *volume, SDL_bool *plein_ecran, int choix)
{
    int i;
    int pX = 46;

    if(choix != -1)
    {
        general = load_img(renderer, fen, "../src/img/general.bmp", 35, 5, general, plein_ecran);
        commandes = load_img(renderer, fen, "../src/img/commandes.bmp", 75, 5, commandes, plein_ecran);
        retour = load_img(renderer, fen, "../src/img/retour.bmp", 5, 5, retour, plein_ecran);

        if(choix == 1)
        {
            retour = load_img(renderer, fen, "../src/img/retour.bmp", 5, 5, retour, plein_ecran);
            fullscreen = load_img(renderer, fen, "../src/img/pleinecran.bmp", 35, 35, fullscreen, plein_ecran);
            classique = load_img(renderer, fen, "../src/img/fenetre.bmp", 65, 35, classique, plein_ecran);
            son = load_img(renderer, fen, "../src/img/son.bmp", 33, 55, son, plein_ecran);
            son_down = load_img(renderer, fen, "../src/img/son_down.bmp", 43, 55, son_down, plein_ecran);
            son_up = load_img(renderer, fen, "../src/img/son_up.bmp", 67, 55, son_up, plein_ecran);

            for(i = 0; i < 100; i += 10)
            {
                if(i < *volume)
                {
                    son_barreup = load_img(renderer, fen, "../src/img/son_barreup.bmp", pX, 55, son_barreup, plein_ecran);
                    pX += 2;
                }
                else
                {
                    son_barredown = load_img(renderer, fen, "../src/img/son_barredown.bmp", pX, 55, son_barredown, plein_ecran);
                    pX += 2;
                }
            }
        }

        if(choix == 2)
        {
            load_img(renderer, fen, "../src/img/haut.bmp", 35, 30, haut, plein_ecran);
            load_img(renderer, fen, "../src/img/gauche.bmp", 35, 40, gauche, plein_ecran);
            load_img(renderer, fen, "../src/img/bas.bmp", 35, 50, bas, plein_ecran);
            load_img(renderer, fen, "../src/img/droite.bmp", 35, 60, droite, plein_ecran);
            load_img(renderer, fen, "../src/img/z.bmp", 65, 30, z, plein_ecran);
            load_img(renderer, fen, "../src/img/q.bmp", 65, 40, q, plein_ecran);
            load_img(renderer, fen, "../src/img/s.bmp", 65, 50, s, plein_ecran);
            load_img(renderer, fen, "../src/img/d.bmp", 65, 60, d, plein_ecran);
        }
    }
    else
    {
        logo = load_img(renderer, fen, "../src/img/logo.bmp", 50, 10, logo, plein_ecran);
        start = load_img(renderer, fen, "../src/img/jouer.bmp", 50, 50, start, plein_ecran);
        option = load_img(renderer, fen, "../src/img/options.bmp", 50, 70, option, plein_ecran);
        quit = load_img(renderer, fen, "../src/img/quitter.bmp", 50, 90, quit, plein_ecran);
    }
}
