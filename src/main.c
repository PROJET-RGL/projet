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

    lab = init_lab(lab, fen, renderer, fenetre, TAILLE_LAB);

    // ------------------------------------------- Création personnage ! ------------------------------------------- //

    perso1 = init_perso(perso1);

    nettoyage_ecran(renderer);

    // ------------------------------------------- Initialisation de l'icon ! ------------------------------------------- //

    image = SDL_LoadBMP("../src/img/Icon.bmp");

    SDL_SetWindowIcon(fen, image);

    // ------------------------------------------- Initialisation du son ! ------------------------------------------- //

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
        printf("ERREUR : %s", Mix_GetError());

    // ------------------------------------------- BOUCLE PRINCIPALE ------------------------------------------- //

    main_theme = Mix_LoadMUS("../src/sound/theme.mp3");

    Mix_PlayMusic(main_theme, -1);

    Mix_VolumeMusic(10);

    int program_lunched = TRUE, jeu_lunched = SDL_TRUE;

    // Boucle de jeu !

    srand(time(NULL));

    while(program_lunched != FALSE)
    {
        exit_menu = load_menu(renderer, fen);

        if(exit_menu == FALSE)
        {
            program_lunched = FALSE;
        }else
        {
            if(lab.tab_salle[TAILLE_LAB-1].nb_mob_mort == 5)
            {
                lab = init_lab(lab, fen, renderer, fenetre, TAILLE_LAB);
                perso1 = init_perso(perso1);
                perso1.tag = 0;
                presserQ = FALSE, presserD = FALSE, presserS = FALSE, presserZ = FALSE;
            }
            jeu_lunched = SDL_TRUE;
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
                                    case SDLK_ESCAPE:
                                        jeu_lunched = SDL_TRUE;
                                        break;

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
                            break;

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

    Mix_FreeMusic(main_theme);
    Mix_CloseAudio();
    clean_ressources(fen, renderer, NULL);
    SDL_Quit();
    return EXIT_SUCCESS;
}