#include "super.h"
#include "labyrinthe.h"
#include "perso.h"
#include "mob.h"
#include "actualisation.h"
#include "fonction_admin.h"
#include "menu.h"
#include "porte.h"
#include "sauvegarde.h"

    int j = 0, exit_menu;
    SDL_Window *fen = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event, event2;
    jeu_t jeu;
    SDL_Rect fenetre;
    SDL_Surface *image = NULL;
    Mix_Music *main_theme;
    int perso_salle = 1, passage;

/**
 * \brief Fonction main du programme
 * \file 'main.c'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.15
 * \date 18 Février 2020
 */

/**
 * @brief C'est le main du programme
 *
 * @param argc nb param
 * @param argv list param
 * @return int - EXIT_SUCCESS
 */

SDL_bool plein_ecran = SDL_FALSE, ingame = SDL_FALSE, charge = SDL_FALSE;

int main(int argc, char **argv)
{
    int volume = 10, touche, presserQ = FALSE, presserD = FALSE, presserS = FALSE, presserZ = FALSE, i = 0, j = 0;

    SDL_Delay(10);
 
    if(creation_fen(&fen, &renderer) != TRUE)
    {
        SDL_ExitWithError("Création du rendu raté, erreur 404 !");
    }

    SDL_SetWindowTitle(fen, "PROJET RGL");

    // ------------------------------------------- Rectangle de la fenetre ------------------------------------------- //

    fenetre.x = 0;
    fenetre.y = 0;

    fenetre.w = FEN_LARGEUR;
    fenetre.h = FEN_HAUTEUR;

    nettoyage_ecran(renderer);

    // ------------------------------------------- Création lab ------------------------------------------- //

    srand(time(NULL));

    // ------------------------------------------- Création personnage ! ------------------------------------------- //

    nettoyage_ecran(renderer);

    // ------------------------------------------- Initialisation de l'icon ! ------------------------------------------- //

    image = SDL_LoadBMP("../src/img/Icon.bmp");

    SDL_SetWindowIcon(fen, image);

    SDL_FreeSurface(image);

    // ------------------------------------------ Init des texture des entités --------------------------------------------- //

    // ------------------------------------------- Initialisation du son ! ------------------------------------------- //

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
        printf("ERREUR : %s", Mix_GetError());

    // ------------------------------------------- BOUCLE PRINCIPALE ------------------------------------------- //

    main_theme = Mix_LoadMUS("../src/sound/theme.mp3");

    Mix_PlayMusic(main_theme, -1);

    Mix_VolumeMusic(volume);

    int program_lunched = TRUE, jeu_lunched = SDL_TRUE;

    //sauvegarde(jeu);

    int premiere_partie = SDL_TRUE;

    // Boucle de jeu !

    srand(time(NULL));
    while(program_lunched != FALSE)
    {
        exit_menu = load_menu(renderer, fen, &volume, &plein_ecran, ingame, &charge, &jeu);
        if(exit_menu == FALSE)
        {
            program_lunched = FALSE;
        }else
        {
            if((charge != 1 || (jeu.lab.tab_salle[TAILLE_LAB-1].nb_mob_mort == 5)) && (premiere_partie == SDL_TRUE))
            {
                jeu.lab = init_lab(jeu.lab, fen, renderer, fenetre, TAILLE_LAB);
                jeu.perso = init_perso(jeu.perso);
                jeu.perso.tag = 0;
                premiere_partie = SDL_FALSE;
                presserQ = FALSE, presserD = FALSE, presserS = FALSE, presserZ = FALSE;
            }else if(charge != 0)
            {
                chargement(&jeu);
                image = SDL_LoadBMP("../src/img/Salle.bmp");

                SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 30, 6, 236));

                jeu.lab.texture = SDL_CreateTextureFromSurface(renderer, image);

                SDL_FreeSurface(image);

                image = SDL_LoadBMP("../src/img/Poro.bmp");

                SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 30, 6, 236));

                for(i = 0; i < jeu.lab.nb; i++)
                {
                    for(j = 0; j < jeu.lab.tab_salle[i].nb_objt; j++)
                    {
                        jeu.lab.tab_salle[i].tab_obj[j].texture = SDL_CreateTextureFromSurface(renderer, image);
                    }
                }
                SDL_FreeSurface(image);

                image = SDL_LoadBMP("../src/img/Poro.bmp");

                SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 30, 6, 236));

                for(i = 0; i < jeu.lab.nb; i++)
                {
                    for(j = 0; j < jeu.lab.tab_salle[i].nb_objt; j++)
                    {
                        jeu.lab.tab_salle[i].tab_mob[j].texture = SDL_CreateTextureFromSurface(renderer, image);
                    }
                }
                SDL_FreeSurface(image);
                nettoyage_ecran(renderer);
                SDL_RenderPresent(renderer);
            }
            jeu_lunched = SDL_TRUE;

            ingame = SDL_TRUE;

            event.key.keysym.sym = 0;
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
                                        if(jeu.perso.velocite.x == VITESSE)                                           // Si j'ai appuyer sur Q et D alors, ça s'annule
                                        {
                                            jeu.perso.velocite.x = 0;
                                        }else if(jeu.perso.velocite.x == 0)
                                            jeu.perso.velocite.x = -VITESSE;                // Si j'ai appuyer sur D alors, le vecteur HORI = VITESSE
                                        presserQ = TRUE;
                                    }
                                    continue;

                                case SDLK_d:
                                    if(presserD == FALSE)
                                    {
                                        if(jeu.perso.velocite.x == -VITESSE)                                           // Si j'ai appuyer sur Q et D alors, ça s'annule
                                        {
                                            jeu.perso.velocite.x = 0;
                                        }else if(jeu.perso.velocite.x == 0)
                                            jeu.perso.velocite.x = VITESSE;                // Si j'ai appuyer sur D alors, le vecteur HORI = VITESSE
                                        presserD = TRUE;
                                    }
                                    continue;

                                case SDLK_s:
                                    if(presserS == FALSE)
                                    {
                                        if(jeu.perso.velocite.y == -VITESSE)                                           // Si j'ai appuyer sur D et Q alors, ça s'annule
                                        {
                                            jeu.perso.velocite.y = 0;
                                        }else if(jeu.perso.velocite.y == 0)
                                            jeu.perso.velocite.y = VITESSE;                // Si j'ai appuyer sur S alors, le vecteur VERTI = VITESSE
                                        presserS = TRUE;
                                    }
                                    continue;

                                case SDLK_z:
                                    if(presserZ == FALSE)
                                    {
                                        if(jeu.perso.velocite.y == VITESSE)                                           // Si j'ai appuyer sur D et Q alors, ça s'annule
                                        {
                                            jeu.perso.velocite.y = 0;
                                        }else if(jeu.perso.velocite.y == 0)
                                            jeu.perso.velocite.y = -VITESSE;                // Si j'ai appuyer sur S alors, le vecteur VERTI = VITESSE
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
                                    case SDLK_ESCAPE:
                                        jeu_lunched = SDL_TRUE;
                                        break;

                                    case SDLK_q:
                                        if(presserQ == TRUE)
                                        {
                                            if(jeu.perso.velocite.x == 0)
                                            {
                                                jeu.perso.velocite.x = VITESSE;
                                            }else if(jeu.perso.velocite.x == -VITESSE)
                                                jeu.perso.velocite.x = 0;
                                            presserQ = FALSE;
                                        }
                                        break;

                                    case SDLK_d:
                                        if(presserD == TRUE)
                                        {
                                            if(jeu.perso.velocite.x == 0)
                                            {
                                                jeu.perso.velocite.x = -VITESSE;
                                            }else if(jeu.perso.velocite.x == VITESSE)
                                                jeu.perso.velocite.x = 0;
                                            presserD = FALSE;
                                        }
                                        break;

                                    case SDLK_s:
                                        if(presserS == TRUE)
                                        {
                                            if(jeu.perso.velocite.y == 0)
                                            {
                                                jeu.perso.velocite.y = -VITESSE;
                                            }else if(jeu.perso.velocite.y == VITESSE)
                                                jeu.perso.velocite.y = 0;
                                            presserS = FALSE;
                                        }
                                        break;

                                    case SDLK_z:
                                        if(presserZ == TRUE)
                                        {
                                            if(jeu.perso.velocite.y == 0)
                                            {
                                                jeu.perso.velocite.y = VITESSE;
                                            }else if(jeu.perso.velocite.y == -VITESSE)
                                                jeu.perso.velocite.y = 0;
                                            presserZ = FALSE;
                                        }
                                        break;

                                    default :
                                        continue;
                                }
                            break;

                        case SDL_MOUSEMOTION :
                            break;

                        default:
                            break;
                    }

                    int i = 0;
                    if(jeu.perso.tag == 0)
                        {
                            jeu.perso = actualisation_salle(jeu.lab, jeu.perso, renderer, fenetre);

                            for(i = 0; i < jeu.lab.tab_salle[jeu.perso.tag].nb_mob; i++)
                            {
                                if(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].pv != 0)
                                {
                                    jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i] = colision_mob(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i], jeu.perso);
                                    if(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].pv == 0)
                                        jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort++;
                                }
                            }

                            // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                            if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[0], jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                            {
                                jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y + jeu.lab.tab_salle[jeu.perso.tag].salle.h ) - (jeu.lab.tab_salle[jeu.perso.tag].porte[0].porte.h)/2 - jeu.perso.perso.h - 100;
                                jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle + 1;
                            }
                            SDL_Delay(10);
                            break;

                        }else if(jeu.perso.tag < TAILLE_LAB - 1 && jeu.perso.tag > 0)
                        {
                            jeu.perso = actualisation_salle(jeu.lab, jeu.perso, renderer, fenetre);

                            for(i = 0; i < jeu.lab.tab_salle[jeu.perso.tag].nb_mob; i++)
                            {
                                if(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].pv != 0)
                                {
                                    jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i] = colision_mob(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i], jeu.perso);
                                    if(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].pv == 0)
                                        jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort++;
                                }
                            }

                            // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                            if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[1], jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                            {
                                printf("Porte du haut touché !\n");
                                jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y + jeu.lab.tab_salle[jeu.perso.tag].salle.h ) - (jeu.lab.tab_salle[jeu.perso.tag].porte[1].porte.h)/2 - jeu.perso.perso.h;
                                if(jeu.perso.tag < 6)
                                    jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle + 1;
                            }else if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[0], jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                            {   // Si on touche la porte du bas, on passe à la salle précédente et on spawn en haut
                                printf("Porte du bas touché !\n");
                                jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y) + (jeu.lab.tab_salle[jeu.perso.tag].porte[0].porte.h) / 2;
                                jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle - 1;
                            }
                            SDL_Delay(10);
                            break;

                        }else if(jeu.perso.tag == TAILLE_LAB - 1)
                        {
                            jeu.perso = actualisation_salle(jeu.lab, jeu.perso, renderer, fenetre);

                            for(i = 0; i < jeu.lab.tab_salle[jeu.perso.tag].nb_mob; i++)
                            {
                                if(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].pv != 0)
                                {
                                    jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i] = colision_mob(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i], jeu.perso);
                                    if (jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].pv == 0)
                                        jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort++;
                                }
                            }

                            if(jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5)
                                jeu_lunched = SDL_FALSE;
                                ingame = SDL_FALSE;

                            // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                                if ((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[1], jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                                {
                                    jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y) + (jeu.lab.tab_salle[jeu.perso.tag].porte[1].porte.h) / 2;
                                    jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle - 1;
                            }
                            SDL_Delay(10);
                            break;
                        }

                }
            }
        }
    }

    Mix_FreeMusic(main_theme);
    Mix_CloseAudio();
    clean_ressources(fen, renderer, NULL);
    SDL_Quit();
    return EXIT_SUCCESS;
}