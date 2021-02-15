#include "super.h"
#include "labyrinthe.h"
#include "perso.h"
#include "mob.h"
#include "actualisation.h"
#include "fonction_admin.h"
#include "menu.h"
#include "porte.h"

    int j = 0, exit_menu;
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
    int touche, presserQ = FALSE, presserD = FALSE, presserS = FALSE, presserZ = FALSE;

    SDL_Delay(10);

    if(creation_fen(&fen, &renderer) != TRUE)
    {
        SDL_ExitWithError("Création du rendu raté, erreur 404 !");
    }

    SDL_SetWindowTitle(fen, "PROJET RGL");

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

    // ------------------------------------------- Initialisation de l'icon ! ------------------------------------------- //

    image = SDL_LoadBMP("../src/img/Icon.bmp");

    SDL_SetWindowIcon(fen, image);

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
                perso1 = init_perso(perso1);
                perso1.tag = 0;
                presserQ = FALSE, presserD = FALSE, presserS = FALSE, presserZ = FALSE;
            }

            while(jeu_lunched != SDL_FALSE)
            {
                    while(SDL_PollEvent(&event) || 1)
                    {
                        switch(event.type)
                        {
                            case SDL_QUIT:
                                program_lunched = SDL_FALSE;
                                jeu_lunched = SDL_FALSE;
                                break;

                            case SDL_KEYDOWN :

                                switch(event.key.keysym.sym)
                                {
                                    case SDLK_ESCAPE:
                                        jeu_lunched = SDL_FALSE;
                                        break;

                                    case SDLK_q:
                                        if(presserQ == FALSE)
                                        {
                                            if(perso1.velocite.x == VITESSE)                                           // Si j'ai appuyer sur Q et D alors, ça s'annule
                                            {
                                                perso1.velocite.x = 0;
                                            }else if(perso1.velocite.x == 0)
                                                perso1.velocite.x = -VITESSE;                // Si j'ai appuyer sur D alors, le vecteur HORI = VITESSE
                                            presserQ = TRUE;
                                        }
                                        continue;

                                    case SDLK_d:
                                        if(presserD == FALSE)
                                        {
                                            if(perso1.velocite.x == -VITESSE)                                           // Si j'ai appuyer sur Q et D alors, ça s'annule
                                            {
                                                perso1.velocite.x = 0;
                                            }else if(perso1.velocite.x == 0)
                                                perso1.velocite.x = VITESSE;                // Si j'ai appuyer sur D alors, le vecteur HORI = VITESSE
                                            presserD = TRUE;
                                        }
                                        continue;

                                    case SDLK_s:
                                        if(presserS == FALSE)
                                        {
                                            if(perso1.velocite.y == -VITESSE)                                           // Si j'ai appuyer sur D et Q alors, ça s'annule
                                            {
                                                perso1.velocite.y = 0;
                                            }else if(perso1.velocite.y == 0)
                                                perso1.velocite.y = VITESSE;                // Si j'ai appuyer sur S alors, le vecteur VERTI = VITESSE
                                            presserS = TRUE;
                                        }
                                        continue;

                                    case SDLK_z:
                                        if(presserZ == FALSE)
                                        {
                                            if(perso1.velocite.y == VITESSE)                                           // Si j'ai appuyer sur D et Q alors, ça s'annule
                                            {
                                                perso1.velocite.y = 0;
                                            }else if(perso1.velocite.y == 0)
                                                perso1.velocite.y = -VITESSE;                // Si j'ai appuyer sur S alors, le vecteur VERTI = VITESSE
                                            presserZ = TRUE;
                                        }
                                        continue;

                                    default :
                                        break;
                                }
                                break;


                            case SDL_KEYUP :

                                switch(event.key.keysym.sym)
                                {
                                    case SDLK_q:
                                        if(presserQ == TRUE)
                                        {
                                            if(perso1.velocite.x == 0)
                                            {
                                                perso1.velocite.x = VITESSE;
                                            }else if(perso1.velocite.x == -VITESSE)
                                                perso1.velocite.x = 0;
                                            presserQ = FALSE;
                                        }
                                        break;

                                    case SDLK_d:
                                        if(presserD == TRUE)
                                        {
                                            if(perso1.velocite.x == 0)
                                            {
                                                perso1.velocite.x = -VITESSE;
                                            }else if(perso1.velocite.x == VITESSE)
                                                perso1.velocite.x = 0;
                                            presserD = FALSE;
                                        }
                                        break;

                                    case SDLK_s:
                                        if(presserS == TRUE)
                                        {
                                            if(perso1.velocite.y == 0)
                                            {
                                                perso1.velocite.y = -VITESSE;
                                            }else if(perso1.velocite.y == VITESSE)
                                                perso1.velocite.y = 0;
                                            presserS = FALSE;
                                        }
                                        break;

                                    case SDLK_z:
                                        if(presserZ == TRUE)
                                        {
                                            if(perso1.velocite.y == 0)
                                            {
                                                perso1.velocite.y = VITESSE;
                                            }else if(perso1.velocite.y == -VITESSE)
                                                perso1.velocite.y = 0;
                                            presserZ = FALSE;
                                        }
                                        break;

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
                            perso1 = actualisation_salle(lab, perso1, renderer, fenetre);

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
                            perso1 = actualisation_salle(lab, perso1, renderer, fenetre);

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
                            perso1 = actualisation_salle(lab, perso1, renderer, fenetre);

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