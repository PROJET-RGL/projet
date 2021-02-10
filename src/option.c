#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "option.h"
#include "fonction_admin.h"

int load_option(SDL_Renderer *renderer, SDL_Window *fen, int FEN_LARGEUR, int FEN_HAUTEUR){

    SDL_Event event;
    SDL_bool att_option = SDL_TRUE;

    fleche = load_img(renderer, fen, FEN_LARGEUR, FEN_HAUTEUR, "src/img/fleche.bmp", 5, 5, fleche);
    fullscreen = load_img(renderer, fen, FEN_LARGEUR, FEN_HAUTEUR, "src/img/fullscreen.bmp", 50, 20, fullscreen);

    while(att_option != SDL_FALSE)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT :
                    att_option = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONUP :
                    if(event.motion.x > fleche.x && event.motion.x < (fleche.x + fleche.w))
                    {
                        if(event.motion.y > fleche.y && event.motion.y < (fleche.y + fleche.h)){
                            att_option = SDL_FALSE;
                        }
                    }
                    if(event.motion.x > fullscreen.x && event.motion.x < (fullscreen.x + fullscreen.w))
                    {
                        if(event.motion.y > fullscreen.y && event.motion.y < (fullscreen.y + fullscreen.h)){
                            SDL_SetWindowFullscreen(fen, SDL_WINDOW_FULLSCREEN);
                        }
                    }
                    break;
                default : 
                    break;
            }
        }
    }

    nettoyage_ecran(renderer);
    load_menu(renderer, fen, FEN_LARGEUR, FEN_HAUTEUR);
}