#include "super.h"
#include "labyrinthe.h"
#include "perso.h"
#include "mob.h"
#include "actualisation.h"
#include "fonction_admin.h"
#include "menu.h"
#include "porte.h"
#include "sauvegarde.h"
#include "combat.h"

    int j = 0, exit_menu;
    SDL_Window *fen = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event, event2;
    jeu_t jeu;
    SDL_Rect fenetre;
    SDL_Surface *image = NULL;
    Mix_Music *main_theme;
    Mix_Chunk *bruit_laser_1, *bruit_laser_3;
    Mix_Chunk *bruit_epee_sortir, *bruit_epee_ranger, *bruit_epee_1, *bruit_epee_3;
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

SDL_bool program_launched, jeu_launched, plein_ecran = SDL_FALSE, ingame = SDL_FALSE, charge;

int main(int argc, char **argv)
{
    int volume = 10, bruitage = volume/4, presserQ = SDL_FALSE, presserD = SDL_FALSE, presserS = SDL_FALSE, presserZ = SDL_FALSE;
    int i = 0, j = 0;

    int cooldown_gauche = SDL_FALSE, cooldown_droit = SDL_FALSE;
    int cliqueGauche, cliqueDroit;
    int mob_cooldown = SDL_FALSE;

    SDL_Delay(10);
 
    if(creation_fen(&fen, &renderer) != SDL_TRUE)
    {
        SDL_ExitWithError("Création du rendu raté, erreur 404 !");
    }

    SDL_SetWindowTitle(fen, "PROJET RGL");

    // ------------------------------------------- Rectangle de la fenetre ------------------------------------------- //

    fenetre.x = 0;
    fenetre.y = 0;

    fenetre.w = FEN_LARGEUR;
    fenetre.h = FEN_HAUTEUR;

    srand(time(NULL));

    nettoyage_ecran(renderer);

    // ------------------------------------------- Initialisation de l'icon ! ------------------------------------------- //

    image = SDL_LoadBMP("../src/img/Icon.bmp");

    SDL_SetWindowIcon(fen, image);

    SDL_FreeSurface(image);

    // ------------------------------------------- Initialisation du son ! ------------------------------------------- //

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
        printf("ERREUR : %s", Mix_GetError());

    // ------------------------------------------- BOUCLE PRINCIPALE ------------------------------------------- //

    main_theme = Mix_LoadMUS("../src/sound/theme.mp3");
    if(main_theme == NULL)
        SDL_ExitWithError("Erreur lors du chargement du theme principal");

    bruit_laser_1 = Mix_LoadWAV("../src/sound/bruit_laser_1.wav");
    if(bruit_laser_1 == NULL)
        SDL_ExitWithError("Erreur lors du chargement du bruitage");

    bruit_laser_3 = Mix_LoadWAV("../src/sound/bruit_laser_3.wav");
    if(bruit_laser_3 == NULL)
        SDL_ExitWithError("Erreur lors du chargement du bruitage");

    bruit_epee_1 = Mix_LoadWAV("../src/sound/bruit_epee_1.wav");
    if(bruit_epee_1 == NULL)
        SDL_ExitWithError("Erreur lors du chargement du bruitage");

    bruit_epee_3 = Mix_LoadWAV("../src/sound/bruit_epee_3.wav");
    if(bruit_epee_3 == NULL)
        SDL_ExitWithError("Erreur lors du chargement du bruitage");

    bruit_epee_sortir = Mix_LoadWAV("../src/sound/bruit_epee_sortir.wav");
    if(bruit_epee_sortir == NULL)
        SDL_ExitWithError("Erreur lors du chargement du bruitage");

    bruit_epee_ranger = Mix_LoadWAV("../src/sound/bruit_epee_ranger.wav");
    if(bruit_epee_ranger == NULL)
        SDL_ExitWithError("Erreur lors du chargement du bruitage");

    Mix_PlayMusic(main_theme, -1);
    Mix_VolumeMusic(volume);


    program_launched = SDL_TRUE, jeu_launched = SDL_TRUE;

    int premiere_partie = SDL_TRUE;

    // Boucle de jeu !

    srand(time(NULL));
    while(program_launched != SDL_FALSE)
    {
        exit_menu = load_menu(renderer, fen, ingame, &volume, &plein_ecran, &charge, &jeu, &program_launched);

        bruitage = volume/4;

        Mix_VolumeChunk(bruit_laser_1, bruitage);
        Mix_VolumeChunk(bruit_laser_3, bruitage);

        if(exit_menu == SDL_FALSE)
        {
            program_launched = SDL_FALSE;
        }else
        {
            if((charge != 1 || (jeu.lab.tab_salle[TAILLE_LAB-1].nb_mob_mort == 5)) && (premiere_partie == SDL_TRUE))
            {
                jeu.lab = init_lab(jeu.lab, fen, renderer, fenetre, TAILLE_LAB);
                jeu.perso = init_perso(jeu.perso);
                jeu.perso.tag = 0;
                premiere_partie = SDL_FALSE;
                presserQ = SDL_FALSE, presserD = SDL_FALSE, presserS = SDL_FALSE, presserZ = SDL_FALSE;
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
            jeu_launched = SDL_TRUE;

            ingame = SDL_TRUE;

            event.key.keysym.sym = 0;
            event.button.button = 0;
            while(jeu_launched != SDL_FALSE)
            {
                while(SDL_PollEvent(&event) || 1)
                {

                    switch(event.type)
                    {
                        case SDL_QUIT:
                            program_launched = SDL_FALSE;
                            jeu_launched = SDL_FALSE;
                            break;

                        case SDL_KEYDOWN :

                            switch(event.key.keysym.sym)
                            {
                                case SDLK_ESCAPE:
                                    jeu_launched = SDL_FALSE;
                                    break;

                                case SDLK_q:
                                    if(presserQ == SDL_FALSE)
                                    {
                                        if(jeu.perso.velocite.x == VITESSE)                // Si j'ai appuyer sur Q et D alors, ça s'annule
                                        {
                                            jeu.perso.velocite.x = 0;
                                        }else if(jeu.perso.velocite.x == 0)
                                            jeu.perso.velocite.x = -VITESSE;               // Si j'ai appuyer sur D alors, le vecteur HORI = VITESSE
                                        presserQ = SDL_TRUE;
                                    }
                                    continue;

                                case SDLK_d:
                                    if(presserD == SDL_FALSE)
                                    {
                                        if(jeu.perso.velocite.x == -VITESSE)               // Si j'ai appuyer sur Q et D alors, ça s'annule
                                        {
                                            jeu.perso.velocite.x = 0;
                                        }else if(jeu.perso.velocite.x == 0)
                                            jeu.perso.velocite.x = VITESSE;                // Si j'ai appuyer sur D alors, le vecteur HORI = VITESSE
                                        presserD = SDL_TRUE;
                                    }
                                    continue;

                                case SDLK_s:
                                    if(presserS == SDL_FALSE)
                                    {
                                        if(jeu.perso.velocite.y == -VITESSE)               // Si j'ai appuyer sur D et Q alors, ça s'annule
                                        {
                                            jeu.perso.velocite.y = 0;
                                        }else if(jeu.perso.velocite.y == 0)
                                            jeu.perso.velocite.y = VITESSE;                // Si j'ai appuyer sur S alors, le vecteur VERTI = VITESSE
                                        presserS = SDL_TRUE;
                                    }
                                    continue;

                                case SDLK_z:
                                    if(presserZ == SDL_FALSE)
                                    {
                                        if(jeu.perso.velocite.y == VITESSE)                // Si j'ai appuyer sur D et Q alors, ça s'annule
                                        {
                                            jeu.perso.velocite.y = 0;
                                        }else if(jeu.perso.velocite.y == 0)
                                            jeu.perso.velocite.y = -VITESSE;               // Si j'ai appuyer sur S alors, le vecteur VERTI = VITESSE
                                        presserZ = SDL_TRUE;
                                    }
                                    continue;

                                case SDLK_1:
                                    if(jeu.perso.arme_actuelle == 1 && jeu.perso.tab_arme[0].tag != 'V')
                                    {
                                        jeu.perso.arme_actuelle = 0;
                                        printf("Changement d'arme a distance !\n");
                                        Mix_PlayChannel(-1, bruit_epee_ranger, 0);
                                    }
                                    break;

                                case SDLK_2:
                                    if(jeu.perso.arme_actuelle == 0 && jeu.perso.tab_arme[1].tag != 'V')
                                    {
                                        jeu.perso.arme_actuelle = 1;
                                        printf("Changement d'arme au corps a corps\n");
                                        Mix_PlayChannel(-1, bruit_epee_sortir, 0);
                                    }
                                    break;

                                default :
                                    break;
                            }
                            break;

                        case SDL_KEYUP :

                            switch(event.key.keysym.sym)
                                {
                                    case SDLK_ESCAPE:
                                        jeu_launched = SDL_TRUE;
                                        break;

                                    case SDLK_q:
                                        if(presserQ == SDL_TRUE)
                                        {
                                            if(jeu.perso.velocite.x == 0)
                                            {
                                                jeu.perso.velocite.x = VITESSE;
                                            }else if(jeu.perso.velocite.x == -VITESSE)
                                                jeu.perso.velocite.x = 0;
                                            presserQ = SDL_FALSE;
                                        }
                                        break;

                                    case SDLK_d:
                                        if(presserD == SDL_TRUE)
                                        {
                                            if(jeu.perso.velocite.x == 0)
                                            {
                                                jeu.perso.velocite.x = -VITESSE;
                                            }else if(jeu.perso.velocite.x == VITESSE)
                                                jeu.perso.velocite.x = 0;
                                            presserD = SDL_FALSE;
                                        }
                                        break;

                                    case SDLK_s:
                                        if(presserS == SDL_TRUE)
                                        {
                                            if(jeu.perso.velocite.y == 0)
                                            {
                                                jeu.perso.velocite.y = -VITESSE;
                                            }else if(jeu.perso.velocite.y == VITESSE)
                                                jeu.perso.velocite.y = 0;
                                            presserS = SDL_FALSE;
                                        }
                                        break;

                                    case SDLK_z:
                                        if(presserZ == SDL_TRUE)
                                        {
                                            if(jeu.perso.velocite.y == 0)
                                            {
                                                jeu.perso.velocite.y = VITESSE;
                                            }else if(jeu.perso.velocite.y == -VITESSE)
                                                jeu.perso.velocite.y = 0;
                                            presserZ = SDL_FALSE;
                                        }
                                        break;

                                    default :
                                        continue;
                                }
                            break;

                        case SDL_MOUSEMOTION :
                            break;

                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT && cooldown_gauche == SDL_FALSE)
                            {
                                cliqueGauche = SDL_GetTicks();
                                cooldown_gauche = SDL_TRUE;
                                if(test_clique_gauche(&jeu))
                                {
                                    if(jeu.perso.arme_actuelle == 0)
                                        Mix_PlayChannel(-1, bruit_laser_1, 0);
                                    else
                                        Mix_PlayChannel(-1, bruit_epee_1, 0);
                                }
                            }
                            if(event.button.button == SDL_BUTTON_RIGHT && cooldown_droit == SDL_FALSE)
                            {
                                cliqueDroit = SDL_GetTicks();
                                cooldown_droit = SDL_TRUE;
                                if(test_clique_droit(&jeu))
                                {
                                    if(jeu.perso.arme_actuelle == 0)
                                        Mix_PlayChannel(-1, bruit_laser_3, 0);
                                    else
                                        Mix_PlayChannel(-1, bruit_epee_3, 0);
                                }
                            }
                            break;

                        default:
                            break;
                    }

                    if(cooldown_gauche == SDL_TRUE)
                    {
                        if(SDL_GetTicks() - cliqueGauche > (jeu.perso.tab_arme[jeu.perso.arme_actuelle].cooldown*100))
                        {
                            cooldown_gauche = SDL_FALSE;
                        }
                        if(SDL_GetTicks() - cliqueDroit > (jeu.perso.tab_arme[jeu.perso.arme_actuelle].cooldown*1000*5))
                        {
                            cooldown_droit = SDL_FALSE;
                        }
                    }

                    int i = 0;
                    if(jeu.perso.tag == 0)                                                                  // Première salle
                    {
                            jeu.perso = actualisation_salle(jeu.lab, jeu.perso, renderer, fenetre);

                            if(SDL_GetTicks() - mob_cooldown >= 1000)
                            {
                                for(i = 0; i < jeu.lab.tab_salle[jeu.perso.tag].nb_mob; i++)
                                {
                                    if(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].statue == VIVANT)
                                    {
                                        if(colision_mob(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i], jeu.perso))
                                        { 
                                            mob_cooldown = SDL_GetTicks();
                                            printf("Le joueur prend 1 degats\n");
                                            jeu.perso.pv--;
                                        }
                                    }
                                }
                            }

                            // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                            if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[0], jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                            {
                                jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y + jeu.lab.tab_salle[jeu.perso.tag].salle.h ) - (jeu.lab.tab_salle[jeu.perso.tag].porte[0].porte.h)/2 - jeu.perso.perso.h - 100;
                                jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle + 1;
                            }

                            if(jeu.perso.pv <= 0)
                            {
                                jeu_launched = SDL_FALSE;
                                ingame = SDL_FALSE;
                                premiere_partie = SDL_TRUE;
                            }

                            SDL_Delay(10);
                            break;

                    }else if(jeu.perso.tag < TAILLE_LAB - 1 && jeu.perso.tag > 0)                               // Salle intermédiaire
                    {
                        jeu.perso = actualisation_salle(jeu.lab, jeu.perso, renderer, fenetre);

                        if(SDL_GetTicks() - mob_cooldown >= 1000)
                        {
                            for(i = 0; i < jeu.lab.tab_salle[jeu.perso.tag].nb_mob; i++)
                            {
                                if(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].statue == VIVANT)
                                {
                                    if(colision_mob(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i], jeu.perso))
                                    { 
                                        mob_cooldown = SDL_GetTicks();
                                        printf("Le joueur prend 1 degats\n");
                                        jeu.perso.pv--;
                                    }
                                }
                            }
                        }

                        // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                        if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[1], jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                        {
                            jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y + jeu.lab.tab_salle[jeu.perso.tag].salle.h ) - (jeu.lab.tab_salle[jeu.perso.tag].porte[1].porte.h)/2 - jeu.perso.perso.h;
                            if(jeu.perso.tag < 6)
                                jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle + 1;

                        }else if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[0], jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                        {   // Si on touche la porte du bas, on passe à la salle précédente et on spawn en haut
                            jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y) + (jeu.lab.tab_salle[jeu.perso.tag].porte[0].porte.h) / 2;
                            jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle - 1;
                        }
                        if(jeu.perso.pv <= 0)
                        {
                            jeu_launched = SDL_FALSE;
                            ingame = SDL_FALSE;
                            premiere_partie = SDL_TRUE;
                        }

                        SDL_Delay(10);
                        break;

                    }else if(jeu.perso.tag == TAILLE_LAB - 1)                                           // Dernière salle
                    {
                        jeu.perso = actualisation_salle(jeu.lab, jeu.perso, renderer, fenetre);

                        if(SDL_GetTicks() - mob_cooldown >= 1000)
                        {
                            for(i = 0; i < jeu.lab.tab_salle[jeu.perso.tag].nb_mob; i++)
                            {
                                if(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].statue == VIVANT)
                                {
                                    if(colision_mob(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i], jeu.perso))
                                    { 
                                        mob_cooldown = SDL_GetTicks();
                                        printf("Le joueur prend 1 degats\n");
                                        jeu.perso.pv--;
                                    }
                                }
                            }
                        }

                        if(jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5)
                        {
                            jeu_launched = SDL_FALSE;
                            ingame = SDL_FALSE;
                            premiere_partie = SDL_TRUE;
                        }else if(jeu.perso.pv <= 0)
                        {
                            jeu_launched = SDL_FALSE;
                            ingame = SDL_FALSE;
                            premiere_partie = SDL_TRUE;
                        }
                        // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                        if ((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[1], jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                        {
                            jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y) + (jeu.lab.tab_salle[jeu.perso.tag].porte[1].porte.h) / 2;
                            jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle - 1;
                        }
                        SDL_Delay(10);
                    }

                    break;
                }
            }
        }
    }
    Mix_FreeChunk(bruit_laser_1);
    Mix_FreeChunk(bruit_laser_3);
    Mix_FreeMusic(main_theme);
    Mix_CloseAudio();
    clean_ressources(fen, renderer, NULL);
    SDL_Quit();
    return EXIT_SUCCESS;
}