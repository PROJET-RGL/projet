#include "objet.h"

objet_t init_obj(objet_t obj)
{

    obj.couleur.r = rand() % 255;
    obj.couleur.v = rand() % 255;
    obj.couleur.b = rand() % 255;

    obj.objet.w = 50;
    obj.objet.h = 50;

    int x = 122 + (rand() % (1174 - obj.objet.w));
    int y = 170 + (rand() % (600 - obj.objet.h));

    obj.objet.x = x;
    obj.objet.y = y;

    return obj;
}

objet_t compare_objet(objet_t obj1, objet_t obj2)
{
    while(obj1.objet.y < (obj2.objet.y + obj2.objet.h) && (obj1.objet.y + obj1.objet.h) > obj2.objet.y && obj1.objet.x < (obj2.objet.x + obj2.objet.w) && (obj1.objet.x + obj1.objet.w) > obj2.objet.x)        
    {    // Tant que le carré A est en contact avec le carré B
        obj2.objet.x = 122 + (rand() % (1174 - obj2.objet.w));
        obj2.objet.y = 170 + (rand() % (560 - obj2.objet.h));
    }
    return obj2;
}