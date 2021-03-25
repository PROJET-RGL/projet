#include "sound.h"

/**
 * \brief Fichier qui influe sur les sound du programme
 * \file 'sound.h'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

Mix_Chunk *init_sound_chunk(Mix_Chunk *chunk, char *src)
{
    chunk = Mix_LoadWAV(src);
    if(chunk == NULL)
        SDL_ExitWithError("Erreur du chargement du bruitage !");

    return chunk;
}

/**
 * @brief Fonction qui gère le volume d'un tableau de bruitage
 * 
 * @param chunk         Tableau de bruitage
 * @param volume        Volume du bruitage
 * @param nb_sons       Nombre de bruitage dans le tableau
 */

void volume_sound(Mix_Chunk *chunk[10], int volume, int nb_sons)
{
    int i = 0;
    for(i = 0; i<nb_sons; i++)
    {
        Mix_VolumeChunk(chunk[i], volume);
    }
}

/**
 * @brief Sert à libérer la mémoire d'un tableau de bruitage
 * 
 * @param chunk     Tableau de bruitage
 * @param nb_sons   Nombre de bruitage dans le tableau
 */

void free_TabChunk(Mix_Chunk *chunk[10], int nb_sons)
{
    int i = 0;
    for(i = 0; i<nb_sons; i++)
    {
        Mix_FreeChunk(chunk[i]);
    }
}