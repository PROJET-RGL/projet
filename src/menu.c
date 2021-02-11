#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "option.h"
#include "menu.h"
#include "fonction_admin.h"

int load_menu(SDL_Renderer *renderer, SDL_Window *fen, int FEN_LARGEUR, int FEN_HAUTEUR){

    SDL_Event event;
    SDL_bool program_lunched = SDL_TRUE;
    SDL_bool att_menu = SDL_TRUE;
    int opt = 0;

    nettoyage_ecran(renderer);

    logo = load_img(renderer, fen, FEN_LARGEUR, FEN_HAUTEUR, "../src/img/logo.bmp", 50, 10, logo);
    start = load_img(renderer, fen, FEN_LARGEUR, FEN_HAUTEUR, "../src/img/start.bmp", 50, 50, start);
    option = load_img(renderer, fen, FEN_LARGEUR, FEN_HAUTEUR, "../src/img/option.bmp", 50, 70, option);
    quit = load_img(renderer, fen, FEN_LARGEUR, FEN_HAUTEUR, "../src/img/quit.bmp", 50, 90, quit);

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
                    if(event.motion.x > quit.x && event.motion.x < (quit.x + quit.w))
                    {
                        if(event.motion.y > quit.y && event.motion.y < (quit.y + quit.h))
                        {
                            att_menu = SDL_FALSE;
                            program_lunched = SDL_FALSE;
                        }
                        if(event.motion.y > start.y && event.motion.y < (start.y + start.h))
                        {
                            att_menu = SDL_FALSE;
                            nettoyage_ecran(renderer);
                        }
                        if(event.motion.y > option.y && event.motion.y < (option.y + option.h))
                        {
                            opt = 1;
                            att_menu = SDL_FALSE;
                        }
                    }
                    break;

                default :
                    break;
            }
        }
    }
    if(opt == 1)
    {
        nettoyage_ecran(renderer);
        load_option(renderer, fen, FEN_LARGEUR, FEN_HAUTEUR);
    }
    return program_lunched;
}

SDL_Rect load_img(SDL_Renderer *renderer, SDL_Window *fen, int FEN_LARGEUR, int FEN_HAUTEUR, char *chemin_img, int pourcentX, int pourcentY, SDL_Rect rect){
    
    SDL_Texture *texture = NULL;
    SDL_Surface *img = NULL;
    
    img = SDL_LoadBMP(chemin_img);

    if(img == NULL){
        clean_ressources(fen, renderer, texture);
        SDL_ExitWithError("Impossible de charger l'image");
    }

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

    rect.x = ((FEN_LARGEUR - rect.w)*pourcentX)/100;
    rect.y = ((FEN_HAUTEUR - rect.h)*pourcentY)/100;
    
    if(SDL_RenderCopy(renderer, texture, NULL, &rect) != 0){
        clean_ressources(fen, renderer, texture);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
    return rect;
}
