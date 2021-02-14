#include "menu.h"

int load_menu(SDL_Renderer *renderer, SDL_Window *fen){

    SDL_Event event;
    SDL_bool program_lunched = SDL_TRUE;
    SDL_bool att_menu = SDL_TRUE;
    int opt = 0;

    nettoyage_ecran(renderer);

    logo = load_img(renderer, fen, "../src/img/logo.bmp", 50, 10, logo);
    start = load_img(renderer, fen, "../src/img/start.bmp", 50, 50, start);
    option = load_img(renderer, fen, "../src/img/option.bmp", 50, 70, option);
    quit = load_img(renderer, fen, "../src/img/quit.bmp", 50, 90, quit);

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
            load_option(renderer, fen);
            opt = 0;
            nettoyage_ecran(renderer);
            logo = load_img(renderer, fen, "../src/img/logo.bmp", 50, 10, logo);
            start = load_img(renderer, fen, "../src/img/start.bmp", 50, 50, start);
            option = load_img(renderer, fen, "../src/img/option.bmp", 50, 70, option);
            quit = load_img(renderer, fen, "../src/img/quit.bmp", 50, 90, quit);
        }
    }
    return program_lunched;
}

int load_option(SDL_Renderer *renderer, SDL_Window *fen)
{

    SDL_Event event;
    SDL_bool att_option = SDL_TRUE;

    fleche = load_img(renderer, fen, "../src/img/fleche.bmp", 5, 5, fleche);
    fullscreen = load_img(renderer, fen, "../src/img/fullscreen.bmp", 50, 20, fullscreen);
    classique = load_img(renderer, fen, "../src/img/classique.bmp", 50, 40, classique);

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
                            SDL_SetWindowPosition(fen, 0, 0);
                            SDL_SetWindowSize(fen, 1920, 1080);
                            SDL_SetWindowBordered(fen, SDL_FALSE);
                        }
                    }
                    if(event.motion.x > classique.x && event.motion.x < (classique.x + classique.w))
                    {
                        if(event.motion.y > classique.y && event.motion.y < (classique.y + classique.h)){
                            SDL_SetWindowPosition(fen, (1920 - FEN_LARGEUR)/2, (1080 - FEN_HAUTEUR)/2);
                            SDL_SetWindowSize(fen, 1440, 900);
                            SDL_SetWindowBordered(fen, SDL_TRUE);
                        }
                    }
                    break;
                default :
                    break;
            }
        }
    }

    nettoyage_ecran(renderer);
    return EXIT_SUCCESS;
}

SDL_Rect load_img(SDL_Renderer *renderer, SDL_Window *fen, char *chemin_img, int pourcentX, int pourcentY, SDL_Rect rect){
    
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
