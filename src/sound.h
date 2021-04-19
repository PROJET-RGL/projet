#ifndef sound_H
#define sound_H

#include "fonction_admin.h"

Mix_Chunk *init_sound_chunk(Mix_Chunk *chunk, char *src);

void volume_sound(Mix_Chunk *chunk[10], int volume, int nb_sons);

void free_TabChunk(Mix_Chunk *chunk[10], int nb_sons);

#endif