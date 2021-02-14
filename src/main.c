#include "super.h"
#include "labyrinthe.h"
#include "perso.h"
#include "mob.h"
#include "actualisation.h"
#include "fonction_admin.h"
#include "menu.h"
#include "porte.h"

    int touche1 = 0, touche2 = 0, j = 0, exit_menu;
    SDL_Window *fen = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event, event2;
    labyrinthe_t lab;
    perso_t perso1;
    objet_t objet1;
    SDL_Rect fenetre;
    SDL_Surface *image = NULL;
    int perso_salle = 1, passage;


int main(int argc, char **argv)
{
    printf("Entrez dans le prog");
    SDL_Delay(10);

    if(creation_fen(&fen, &renderer) != TRUE)
    {
        SDL_ExitWithError("Création du rendu raté, erreur 404 !");
    }

    // ------------------------------------------- Rectangle de la fenetre ------------------------------------------- //

    fenetre.x = 0;
    fenetre.y = 0;

    fenetre.h = FEN_HAUTEUR;
    fenetre.w = FEN_LARGEUR;

    nettoyage_ecran(renderer);

    // ------------------------------------------- Création lab ------------------------------------------- //

    srand(time(NULL));

    lab = init_lab(lab, TAILLE_LAB);

    // ------------------------------------------- Création personnage ! ------------------------------------------- //

    perso1 = init_perso(perso1);

    // ------------------------------------------- Initialisation de la texture des salles !!! ------------------------------------------- //

    image = SDL_LoadBMP("../src/img/Salle.bmp");

    if(image == NULL)
    {
        clean_ressources(fen, renderer, NULL);
        SDL_ExitWithError("Erreur du chargement de l'image");
    }

    int i = 0;

    lab.texture = SDL_CreateTextureFromSurface(renderer, image);

    if(lab.texture == NULL)
        {
            clean_ressources(fen, renderer, lab.texture);
            SDL_ExitWithError("Erreur de création de la texture");
        }

    if(SDL_QueryTexture(lab.texture, NULL, NULL, &fenetre.w, &fenetre.h) != 0)
        {
            clean_ressources(fen, renderer, lab.texture);
            SDL_ExitWithError("Erreur de chargement de la texture");
        }

    SDL_FreeSurface(image);



    // ------------------------------------------- Initialisation des textures objets ! ------------------------------------------- //

    image = SDL_LoadBMP("../src/img/Poro.bmp");

    if(image == NULL)
    {
        clean_ressources(fen, renderer, NULL);
        SDL_ExitWithError("Erreur du chargement de l'image");
    }

    SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 30, 6, 236));

    for(j = 0 ; j < lab.nb ; j++)
    {
        for(i = 0; i < lab.tab_salle[j].nb_objt; i++)
        {
            lab.tab_salle[j].tab_obj[i].text_objet = SDL_CreateTextureFromSurface(renderer, image);

            if(lab.tab_salle[j].tab_obj[i].text_objet == NULL)
            {
                clean_ressources(fen, renderer, lab.tab_salle[j].tab_obj[i].text_objet);
                SDL_ExitWithError("Erreur de création de la texture");
            }

            if(SDL_QueryTexture(lab.tab_salle[j].tab_obj[i].text_objet, NULL, NULL, &lab.tab_salle[j].tab_obj[i].objet.w, &lab.tab_salle[j].tab_obj[i].objet.h) != 0)
            {
                clean_ressources(fen, renderer, lab.tab_salle[j].tab_obj[i].text_objet);
                SDL_ExitWithError("Erreur de chargement de la texture");
            }

            if(SDL_RenderCopy(renderer, lab.tab_salle[j].tab_obj[i].text_objet, NULL, &lab.tab_salle[j].tab_obj[i].objet) != 0)
            {
                clean_ressources(fen, renderer, lab.tab_salle[j].tab_obj[i].text_objet);
                SDL_ExitWithError("Impossible d'afficher la texture !\n");
            }
        }
    }
    SDL_FreeSurface(image);



    // ------------------------------------------- Initialisation des textures mobs ! ------------------------------------------- //

    image = SDL_LoadBMP("../src/img/Poro.bmp");

    if(image == NULL)
    {
        clean_ressources(fen, renderer, NULL);
        SDL_ExitWithError("Erreur du chargement de l'image");
    }

    SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 30, 6, 236));

    for(j = 0 ; j < lab.nb ; j++)
    {
        for(i = 0; i < lab.tab_salle[j].nb_mob; i++)
        {
            lab.tab_salle[j].tab_mob[i].texture = SDL_CreateTextureFromSurface(renderer, image);
            if( lab.tab_salle[j].tab_mob[i].texture == NULL)
            {
                clean_ressources(fen, renderer, lab.tab_salle[j].tab_mob[i].texture);
                SDL_ExitWithError("Erreur de création de la texture");
            }

            if(SDL_QueryTexture(lab.tab_salle[j].tab_mob[i].texture, NULL, NULL, &lab.tab_salle[j].tab_mob[i].mob.w, &lab.tab_salle[j].tab_mob[i].mob.h) != 0)
            {
                clean_ressources(fen, renderer, lab.tab_salle[j].tab_mob[i].texture);
                SDL_ExitWithError("Erreur de chargement de la texture");
            }

            if(SDL_RenderCopy(renderer, lab.tab_salle[j].tab_mob[i].texture, NULL, &lab.tab_salle[j].tab_mob[i].mob) != 0)
            {
                clean_ressources(fen, renderer, lab.tab_salle[j].tab_mob[i].texture);
                SDL_ExitWithError("Impossible d'afficher la texture !\n");
            }
        }
    }
    SDL_FreeSurface(image);

    nettoyage_ecran(renderer);


    // ------------------------------------------- BOUCLE PRINCIPALE ------------------------------------------- //

    int program_lunched = TRUE, jeu_lunched = SDL_TRUE;

    // Boucle de jeu !

    srand(time(NULL));

    while(program_lunched != FALSE)
    {
        jeu_lunched = SDL_TRUE;
        exit_menu = load_menu(renderer, fen);

        if(exit_menu == FALSE)
        {
            program_lunched = FALSE;
        }else
        {
            if(lab.tab_salle[TAILLE_LAB-1].nb_mob_mort == 5)
            {
                lab = init_lab(lab, TAILLE_LAB);
                perso1.tag = 0;
            }

            while(jeu_lunched != SDL_FALSE)
            {
                    while(SDL_PollEvent(&event))
                    {
                        switch(event.type)
                        {
                            case SDL_QUIT:
                                program_lunched = SDL_FALSE;
                                jeu_lunched = SDL_FALSE;
                                break;

                            case SDL_KEYUP :

                                switch(event.key.keysym.sym)
                                {
                                    case SDLK_q:
                                        if(touche1 == 'Q')
                                        {
                                            touche1 = 0;
                                        }
                                        if(touche2 == 'Q')
                                        {
                                            touche2 = 0;
                                        }
                                        continue;

                                    case SDLK_d:
                                        if(touche1 == 'D')
                                        {
                                            touche1 = 0;
                                        }
                                        if(touche2 == 'D')
                                        {
                                            touche2 = 0;
                                        }
                                        continue;

                                    case SDLK_s:
                                        if(touche1 == 'S')
                                        {
                                            touche1 = 0;
                                        }
                                        if(touche2 == 'S')
                                        {
                                            touche2 = 0;
                                        }
                                        continue;

                                    case SDLK_z:
                                        if(touche1 == 'Z')
                                        {
                                            touche1 = 0;
                                        }
                                        if(touche2 == 'Z')
                                        {
                                            touche2 = 0;
                                        }
                                        continue;

                                    default :
                                        continue;
                                }
                                break;

                            case SDL_KEYDOWN :

                                switch(event.key.keysym.sym)
                                {
                                    case SDLK_ESCAPE:
                                        jeu_lunched = SDL_FALSE;
                                        break;

                                    case SDLK_q:
                                        if(touche1 == 0 && touche1 != 'Q')
                                        {
                                            touche1 = 'Q';
                                        }
                                        else if(touche2 == 0 && touche1 != 'Q')
                                        {
                                            touche2 = 'Q';
                                        }
                                        continue;

                                        case SDLK_d:
                                            if(touche1 == 0 && touche1 != 'D')
                                            {
                                                touche1 = 'D';
                                            }
                                            else if(touche2 == 0 && touche1 != 'D')
                                            {
                                                touche2 = 'D';
                                            }
                                            continue;

                                        case SDLK_s:
                                            if(touche1 == 0 && touche1 != 'S')
                                            {
                                                touche1 = 'S';
                                            }
                                            else if(touche2 == 0 && touche1 != 'S')
                                            {
                                                touche2 = 'S';
                                            }
                                            continue;

                                        case SDLK_z:
                                            if(touche1 == 0 && touche1 != 'Z')
                                            {
                                                touche1 = 'Z';
                                            }
                                            else if(touche2 == 0 && touche1 != 'Z')
                                            {
                                                touche2 = 'Z';
                                            }
                                                continue;

                                        default :
                                            continue;
                                }
                                break;

                            case SDL_MOUSEMOTION :
                                continue;

                            default:
                                break;
                        }

                        int i = 0;

                        if(perso1.tag == 0)
                        {
                            perso1 = actualisation_salle(lab, perso1, renderer, fenetre, touche1, touche2);

                            for(i = 0; i < lab.tab_salle[perso1.tag].nb_mob; i++)
                            {
                                if(lab.tab_salle[perso1.tag].tab_mob[i].pv != 0)
                                {
                                    lab.tab_salle[perso1.tag].tab_mob[i] = colision_mob(lab.tab_salle[perso1.tag].tab_mob[i], perso1);
                                    if(lab.tab_salle[perso1.tag].tab_mob[i].pv == 0)
                                        lab.tab_salle[perso1.tag].nb_mob_mort++;
                                }
                            }

                            // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                            if((collision_porte(perso1, lab.tab_salle[perso1.tag].porte[0], lab.tab_salle[perso1.tag].porte[0].salle_entree, lab.tab_salle[perso1.tag].porte[0].salle_dest) != lab.tab_salle[perso1.tag].tag_salle) && (lab.tab_salle[perso1.tag].nb_mob_mort == 5))
                            {
                                perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y + lab.tab_salle[perso1.tag].salle.h ) - (lab.tab_salle[perso1.tag].porte[0].porte.h)/2 - perso1.perso.h - 100;
                                perso1.tag = lab.tab_salle[perso1.tag].tag_salle + 1;
                            }
                            SDL_Delay(10);
                            break;

                        }else if(perso1.tag < TAILLE_LAB - 1 && perso1.tag > 0)
                        {
                            perso1 = actualisation_salle(lab, perso1, renderer, fenetre, touche1, touche2);

                            for(i = 0; i < lab.tab_salle[perso1.tag].nb_mob; i++)
                            {
                                if(lab.tab_salle[perso1.tag].tab_mob[i].pv != 0)
                                {
                                    lab.tab_salle[perso1.tag].tab_mob[i] = colision_mob(lab.tab_salle[perso1.tag].tab_mob[i], perso1);
                                    if(lab.tab_salle[perso1.tag].tab_mob[i].pv == 0)
                                        lab.tab_salle[perso1.tag].nb_mob_mort++;
                                }
                            }

                            // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                            if((collision_porte(perso1, lab.tab_salle[perso1.tag].porte[1], lab.tab_salle[perso1.tag].porte[1].salle_entree, lab.tab_salle[perso1.tag].porte[1].salle_dest) != lab.tab_salle[perso1.tag].tag_salle) && (lab.tab_salle[perso1.tag].nb_mob_mort == 5))
                            {
                                printf("Porte du haut touché !\n");
                                perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y + lab.tab_salle[perso1.tag].salle.h ) - (lab.tab_salle[perso1.tag].porte[1].porte.h)/2 - perso1.perso.h;
                                if(perso1.tag < 6)
                                    perso1.tag = lab.tab_salle[perso1.tag].tag_salle + 1;

                            }else if((collision_porte(perso1, lab.tab_salle[perso1.tag].porte[0], lab.tab_salle[perso1.tag].porte[0].salle_entree, lab.tab_salle[perso1.tag].porte[0].salle_dest) != lab.tab_salle[perso1.tag].tag_salle) && (lab.tab_salle[perso1.tag].nb_mob_mort == 5))
                            {   // Si on touche la porte du bas, on passe à la salle précédente et on spawn en haut
                                printf("Porte du bas touché !\n");
                                perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y) + (lab.tab_salle[perso1.tag].porte[0].porte.h)/2;
                                perso1.tag = lab.tab_salle[perso1.tag].tag_salle - 1;
                            }
                            SDL_Delay(10);
                            break;

                        }else if(perso1.tag == TAILLE_LAB - 1)
                        {
                            perso1 = actualisation_salle(lab, perso1, renderer, fenetre, touche1, touche2);

                            for(i = 0; i < lab.tab_salle[perso1.tag].nb_mob; i++)
                            {
                                if(lab.tab_salle[perso1.tag].tab_mob[i].pv != 0)
                                {
                                    lab.tab_salle[perso1.tag].tab_mob[i] = colision_mob(lab.tab_salle[perso1.tag].tab_mob[i], perso1);
                                    if(lab.tab_salle[perso1.tag].tab_mob[i].pv == 0)
                                        lab.tab_salle[perso1.tag].nb_mob_mort++;
                                }
                            }

                            if(lab.tab_salle[perso1.tag].nb_mob_mort == 5)
                                jeu_lunched = SDL_FALSE;

                            // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                            if((collision_porte(perso1, lab.tab_salle[perso1.tag].porte[1], lab.tab_salle[perso1.tag].porte[1].salle_entree, lab.tab_salle[perso1.tag].porte[1].salle_dest) != lab.tab_salle[perso1.tag].tag_salle) && (lab.tab_salle[perso1.tag].nb_mob_mort == 5))
                            {
                                perso1.perso.y = (lab.tab_salle[perso1.tag].salle.y) + (lab.tab_salle[perso1.tag].porte[1].porte.h)/2;
                                perso1.tag = lab.tab_salle[perso1.tag].tag_salle - 1;
                            }
                            SDL_Delay(10);
                            break;
                        }

                    }
            }
        }
    }
    clean_ressources(fen, renderer, NULL);
    SDL_Quit();
    return EXIT_SUCCESS;
}