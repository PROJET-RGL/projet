#include "son.h"

void load_son(char *chemin_son)
{
    SDL_Window *ecran;
    SDL_Renderer *rendu;
    

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
        printf("ERREUR : %s", Mix_GetError());

    

    


}

