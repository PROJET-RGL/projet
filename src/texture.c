#include "texture.h"

/**
 * \brief Header des fonctions agissant sur les textures du programmes
 * \file 'texture.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 mars 2021
 */

/**
 * @brief Inititalisation de la texture
 * 
 * @param renderer Attributs pour l'affiche d'une fenêtre
 * @param fen Fenêtre sur laquelle on veut afficher les options
 * @param chemin_image Chemin relatif jusqu'à l'image
 * @return SDL_Texture* Retourne la texture initialiser
 */

SDL_Texture *init_texture(SDL_Renderer *renderer, SDL_Window *fen, char *chemin_image)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *image = NULL;
    
    image = SDL_LoadBMP(chemin_image);

    if(image == NULL){
        clean_ressources(fen, renderer, texture);
        SDL_ExitWithError("Impossible de charger l'image");
    }

    SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 30, 6, 236));

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if(texture == NULL){
        clean_ressources(fen, renderer, texture);
        SDL_ExitWithError("Impossible de créer la texture");
    }

    return texture;
}

/**
 * @brief Affiche la texture rentrer en paramètre
 * 
 * @param renderer Attributs pour l'affiche d'une fenêtre
 * @param fen Fenêtre sur laquelle on veut afficher les options
 * @param texture Texture à afficher
 * @param rect Rectangle dans lequel on affiche la texture
 * @param plein_ecran Indique si le jeu est en plein écran
 * @param pourcentX Indique la position X de l'image en pourcentage
 * @param pourcentX Indique la position Y de l'image en pourcentage
 * @return SDL_Rect 
 */

SDL_Rect afficher_texture(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *texture, SDL_Rect rect, SDL_bool plein_ecran, int pourcentX, int pourcentY)
{
    if(SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) != 0){
        clean_ressources(fen, renderer, texture);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }

    if(!plein_ecran)
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

    return rect;
}

/**
 * @brief On charge les textures du menu
 * 
 * @param renderer Rendu d'acquisition
 * @param fen  Fenêtre d'acquisition 
 * @param en_partie Oui ou Non
 * @param texture Tableau de texture
 */

void charger_textures_menu(SDL_Renderer *renderer, SDL_Window *fen, SDL_bool en_partie, SDL_Texture *texture[9])
{
    texture[0] = init_texture(renderer, fen, "../src/img/logo.bmp");

    texture[1] = init_texture(renderer, fen, "../src/img/jouer.bmp");
    texture[2] = init_texture(renderer, fen, "../src/img/continuer.bmp");

    texture[3] = init_texture(renderer, fen, "../src/img/options.bmp");

    texture[4] = init_texture(renderer, fen, "../src/img/quitter.bmp");
    texture[5] = init_texture(renderer, fen, "../src/img/sauv_quitter.bmp");

    texture[6] = init_texture(renderer, fen, "../src/img/nouvelle.bmp");
    texture[7] = init_texture(renderer, fen, "../src/img/charger.bmp");
    texture[8] = init_texture(renderer, fen, "../src/img/retour.bmp");
}

/**
 * @brief On charge les textures de l'option
 * 
 * @param renderer Rendu d'acquisition
 * @param fen  Fenêtre d'acquisition
 * @param texture Tableau de texture
 */

void charger_textures_options(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *texture[10])
{
    texture[0] = init_texture(renderer, fen, "../src/img/general.bmp");
    texture[1] = init_texture(renderer, fen, "../src/img/commandes.bmp");
    texture[2] = init_texture(renderer, fen, "../src/img/retour.bmp");
    texture[3] = init_texture(renderer, fen, "../src/img/pleinecran.bmp");
    texture[4] = init_texture(renderer, fen, "../src/img/fenetre.bmp");
    texture[5] = init_texture(renderer, fen, "../src/img/son.bmp");
    texture[6] = init_texture(renderer, fen, "../src/img/son_down.bmp");
    texture[7] = init_texture(renderer, fen, "../src/img/son_up.bmp");
    texture[8] = init_texture(renderer, fen, "../src/img/son_barreup.bmp");
    texture[9] = init_texture(renderer, fen, "../src/img/son_barredown.bmp");
}

/**
 * @brief 
 * 
 * @param renderer 
 * @param fen 
 * @param texture 
 */

void charger_textures_commandes(SDL_Renderer *renderer, SDL_Window *fen, SDL_Texture *texture[8])
{
    texture[0] = init_texture(renderer, fen, "../src/img/haut.bmp");
    texture[1] = init_texture(renderer, fen, "../src/img/gauche.bmp");
    texture[2] = init_texture(renderer, fen, "../src/img/bas.bmp");
    texture[3] = init_texture(renderer, fen, "../src/img/droite.bmp");
    texture[4] = init_texture(renderer, fen, "../src/img/z.bmp");
    texture[5] = init_texture(renderer, fen, "../src/img/q.bmp");
    texture[6] = init_texture(renderer, fen, "../src/img/s.bmp");   
    texture[7] = init_texture(renderer, fen, "../src/img/d.bmp");   
}