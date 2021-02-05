#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <time.h>

#include "perso.h"
#include "fonction_admin.h"
#include "salle.h"

SDL_Rect init_obj(SDL_Rect obj)
{

    obj.w = 50;
    obj.h = 50;

    int x = 144 + (rand() % (1152 - obj.w));
    int y = 90 + (rand() % (720 - obj.h));

    printf("%d, %d\n", x, y);

    obj.x = x;
    obj.y = y;

    return obj;
}