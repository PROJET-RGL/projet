#include "sound.h"
#include "labyrinthe.h"
#include "perso.h"
#include "mob.h"
#include "actualisation.h"
#include "fonction_admin.h"
#include "menu.h"
#include "porte.h"
#include "sauvegarde.h"
#include "combat.h"
#include "hud.h"

    int j = 0, exit_menu;
    SDL_Window *fen = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event, event2;
    jeu_t jeu;
    SDL_Rect fenetre;
    SDL_Surface *image = NULL;
    Mix_Music *main_theme = NULL;

    Mix_Chunk *pistolet[2] = {NULL, NULL};
    Mix_Chunk *epee[4] = {NULL, NULL, NULL, NULL};

    int perso_salle = 1, passage;

    SDL_Texture *textures_menu[9], *textures_options[10], *textures_commandes[8], *textures_items[10], *textures_perso[2], *pause, *mort, *gagner;

/**
 * \brief Fonction main du programme
 * \file 'main.c'
 * \author Boitiere Dorian, Beuvier Jules, Boucharinc Billy, André Thomas
 * \version 0.0.2
 * \date 22 Mars 2021
 */

/**
 * @brief C'est le main du programme
 *
 * @param argc nb param
 * @param argv list param
 * @return int - EXIT_SUCCESS
 */

SDL_bool program_launched, jeu_launched, plein_ecran = SDL_FALSE, en_partie = SDL_FALSE, charge;

int main(int argc, char **argv)
{
    
    int volume = 30, bruitage = volume/4, presserQ = SDL_FALSE, presserD = SDL_FALSE, presserS = SDL_FALSE, presserZ = SDL_FALSE;
    int i = 0, j = 0;

    int cooldown_gauche[2] = {SDL_FALSE, SDL_FALSE}, cooldown_droit[2] = {SDL_FALSE, SDL_FALSE};
    int cliqueGauche[2], cliqueDroit[2];
    int mob_cooldown = SDL_FALSE;

    SDL_bool est_pause = SDL_FALSE;
    SDL_Rect pos_pause, pos_mort, pos_gagner;
    int temps_mort = 0, temps_gagner = 0;

    char *pistolet_src[100];
    pistolet_src[0] = "../src/sound/bruit_laser_1.wav";
    pistolet_src[1] = "../src/sound/bruit_laser_3.wav";

    char *epee_src[100];
    epee_src[0] = "../src/sound/bruit_epee_1.wav";
    epee_src[1] = "../src/sound/bruit_epee_3.wav";
    epee_src[2] = "../src/sound/bruit_epee_ranger.wav";
    epee_src[3] = "../src/sound/bruit_epee_sortir.wav";

    SDL_Delay(10);

    if(creation_fen(&fen, &renderer) != SDL_TRUE)
    {
        SDL_ExitWithError("Création du rendu raté, erreur 404 !");
    }

    SDL_SetWindowTitle(fen, "PROJET RGL");

    // ------------------------------------------- Initialisation de toutes les textures ------------------------------------------- //

    charger_textures_menu(renderer, fen, en_partie, textures_menu);
    charger_textures_options(renderer, fen, textures_options);
    charger_textures_commandes(renderer, fen, textures_commandes);
    charger_textures_items(renderer, fen, textures_items);
    jeu.perso.inv.texture_case = init_texture(renderer, fen, "../src/img/case_inventaire.bmp");
    jeu.perso.inv.texture_inventaire = init_texture(renderer, fen, "../src/img/inventaire.bmp");
    jeu.perso.inv.texture_inventaire_armes = init_texture(renderer, fen, "../src/img/inventaire_armes.bmp");
    pause = init_texture(renderer, fen, "../src/img/pause.bmp");
    mort = init_texture(renderer, fen, "../src/img/mort.bmp");
    gagner = init_texture(renderer, fen, "../src/img/gagner.bmp");
    jeu.perso.textures_perso[0] = init_texture(renderer, fen, "../src/img/perso_arme.bmp");
    jeu.perso.textures_perso[1] = init_texture(renderer, fen, "../src/img/perso_sabre.bmp");
    jeu.hud.arme_dist = init_texture(renderer, fen, "../src/img/arme.bmp");
    jeu.hud.arme_cac = init_texture(renderer, fen, "../src/img/sabre.bmp");


    // ------------------------------------------- Rectangle de la fenetre ------------------------------------------- //

    jeu = init_hud(&jeu);

    jeu = init_texture_hud(&jeu);

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

    for(i = 0; i<2; i++)
        pistolet[i] = init_sound_chunk(pistolet[i], pistolet_src[i]);

    for(i = 0; i<4; i++)
        epee[i] = init_sound_chunk(epee[i], epee_src[i]);

    Mix_PlayMusic(main_theme, -1);
    Mix_VolumeMusic(volume);

    program_launched = SDL_TRUE, jeu_launched = SDL_TRUE;

    int premiere_partie = SDL_TRUE;

    // Boucle de jeu !

    srand(time(NULL));
    while(program_launched != SDL_FALSE)
    {
        exit_menu = load_menu(renderer, fen, textures_menu, textures_options, textures_commandes, &volume, &charge, &jeu, &plein_ecran, &program_launched, en_partie);

        bruitage = volume/4;

        volume_sound(pistolet, bruitage, 2);
        volume_sound(epee, bruitage, 4);

        if(exit_menu == SDL_FALSE)
        {
            program_launched = SDL_FALSE;
        }else
        {
            if((charge != 1 || (jeu.lab.tab_salle[TAILLE_LAB-1].nb_mob_mort == 5)) && (premiere_partie == SDL_TRUE))
            {
                jeu.lab = init_lab(jeu.lab, fen, renderer, fenetre, TAILLE_LAB);
                jeu.perso = init_perso(&jeu);
                jeu.perso.tag = 0;
                premiere_partie = SDL_FALSE;
                presserQ = SDL_FALSE, presserD = SDL_FALSE, presserS = SDL_FALSE, presserZ = SDL_FALSE;
            }else if(charge != 0)
            {
                chargement(&jeu);

                /*
                        On charge les textures des différentes stuctures de la partie
                */

               // Salle

                image = SDL_LoadBMP("../src/img/Salle.bmp");

                SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 30, 6, 236));

                jeu.lab.texture = SDL_CreateTextureFromSurface(renderer, image);

                SDL_FreeSurface(image);

                // Objet

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

                // Mob

                switch(DIFFICULTY)
                {
                    case 'P':
                        image = SDL_LoadBMP("../src/img/mob_p.bmp");
                        break;

                    case 'M':
                        image = SDL_LoadBMP("../src/img/mob_m.bmp");
                        break;

                    case 'G':
                        image = SDL_LoadBMP("../src/img/mob_g.bmp");
                        break;
                }

                SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 30, 6, 236));

                for(i = 0; i < jeu.lab.nb; i++)
                {
                    for(j = 0; j < jeu.lab.tab_salle[i].nb_objt; j++)
                    {
                        jeu.lab.tab_salle[i].tab_mob[j].texture = SDL_CreateTextureFromSurface(renderer, image);
                    }
                }

                // HUD

                affichage_hud(renderer, &jeu, fen);

                // Destruction variable

                SDL_FreeSurface(image);
                nettoyage_ecran(renderer);
                SDL_RenderPresent(renderer);

            }
            jeu_launched = SDL_TRUE;

            en_partie = SDL_TRUE;

            event.key.keysym.sym = 0;
            event.button.button = 0;
            while(jeu_launched != SDL_FALSE)
            {
                while(SDL_PollEvent(&event) || TRUE)
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
                                    printf("Test ESCAPE\n");
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
                                        DEBUG_MODE
                                            printf("Changement d'arme a distance !\n");
                                        Mix_PlayChannel(-1, epee[3], 0);
                                    }
                                    break;

                                case SDLK_2:
                                    if(jeu.perso.arme_actuelle == 0 && jeu.perso.tab_arme[1].tag != 'V')
                                    {
                                        jeu.perso.arme_actuelle = 1;
                                        DEBUG_MODE
                                            printf("Changement d'arme au corps a corps\n");
                                        Mix_PlayChannel(-1, epee[2], 0);
                                    }
                                    break;

                                case SDLK_p:
                                    afficher_texture(renderer, fen, pause, pos_pause, plein_ecran, 50, 50, -1, -1);
                                    SDL_RenderPresent(renderer);
                                    Mix_PauseMusic();
                                    est_pause = SDL_TRUE;
                                    while(est_pause)
                                    {
                                        while(SDL_PollEvent(&event))
                                        {
                                            switch(event.type)
                                            {
                                                case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                        case SDLK_p:
                                                        case SDLK_ESCAPE:
                                                            est_pause = SDL_FALSE;
                                                            break;
                                                        default:
                                                            break;
                                                    }

                                                default:
                                                    break;

                                            }
                                        }
                                    }
                                    event.key.keysym.sym = 0;
                                    jeu.perso.velocite.x = 0;
                                    jeu.perso.velocite.y = 0;

                                    presserZ = SDL_FALSE;
                                    presserQ = SDL_FALSE;
                                    presserS = SDL_FALSE;
                                    presserD = SDL_FALSE;

                                    Mix_ResumeMusic();

                                    actualisation_salle(&jeu, renderer, fenetre, fen);
                                    break;

                                case SDLK_i:
                                    ouvrir_inventaire(renderer, fen, &jeu, plein_ecran);

                                    event.key.keysym.sym = 0;
                                    jeu.perso.velocite.x = 0;
                                    jeu.perso.velocite.y = 0;

                                    presserZ = SDL_FALSE;
                                    presserQ = SDL_FALSE;
                                    presserS = SDL_FALSE;
                                    presserD = SDL_FALSE;
                                    break;
                                
                                default :
                                    break;
                                
                            }
                            break;

                        case SDL_KEYUP :

                            switch(event.key.keysym.sym)
                                {
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

                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                switch(jeu.perso.tab_arme[jeu.perso.arme_actuelle].type)
                                {
                                    case 'C':
                                        if(cooldown_gauche[1] == SDL_FALSE)
                                        {
                                            cliqueGauche[1] = SDL_GetTicks();
                                            cooldown_gauche[1] = SDL_TRUE;
                                            if(test_clique_gauche(&jeu))
                                            {
                                                Mix_PlayChannel(-1, epee[0], 0);
                                            }
                                        }
                                        break;

                                    case 'D':
                                        if(cooldown_gauche[0] == SDL_FALSE)
                                        {
                                            cliqueGauche[0] = SDL_GetTicks();
                                            cooldown_gauche[0] = SDL_TRUE;
                                            if(test_clique_gauche(&jeu))
                                            {
                                                Mix_PlayChannel(-1, pistolet[0], 0);
                                            }
                                        }
                                        break;

                                    default:
                                        break;
                                }
                            }
                            if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                switch(jeu.perso.tab_arme[jeu.perso.arme_actuelle].type)
                                {
                                    case 'C':
                                        if(cooldown_droit[1] == SDL_FALSE)
                                        {
                                            cliqueDroit[1] = SDL_GetTicks();
                                            cooldown_droit[1] = SDL_TRUE;
                                            if(test_clique_droit(&jeu))
                                            {
                                                Mix_PlayChannel(-1, epee[1], 0);
                                            }
                                        }
                                        break;

                                    case 'D':
                                        if(cooldown_droit[0] == SDL_FALSE)
                                        {
                                            cliqueDroit[0] = SDL_GetTicks();
                                            cooldown_droit[0] = SDL_TRUE;
                                            if(test_clique_droit(&jeu))
                                            {
                                                Mix_PlayChannel(-1, pistolet[1], 0);
                                            }
                                        }
                                        break;

                                    default:
                                        break;
                                }
                            }
                            break;

                        default:
                            break;
                    }
                    if(SDL_GetTicks() - cliqueGauche[0] > (jeu.perso.tab_arme[0].cooldown*100))
                    {
                        cooldown_gauche[0] = SDL_FALSE;
                    }

                    if(SDL_GetTicks() - cliqueGauche[1] > (jeu.perso.tab_arme[1].cooldown*100))
                    {
                        cooldown_gauche[1] = SDL_FALSE;
                    }

                    if(SDL_GetTicks() - cliqueDroit[0] > (jeu.perso.tab_arme[0].cooldown*1000*5))
                    {
                        cooldown_droit[0] = SDL_FALSE;
                    }

                    if(SDL_GetTicks() - cliqueDroit[1] > (jeu.perso.tab_arme[1].cooldown*1000*5))
                    {
                        cooldown_droit[1] = SDL_FALSE;
                    }

                    int i = 0;

                    jeu = actualisation_salle(&jeu, renderer, fenetre, fen);
                    affichage_hud(renderer, &jeu, fen);
                    SDL_RenderPresent(renderer);

                    if(SDL_GetTicks() - mob_cooldown >= 1000)
                    {
                        for(i = 0; i < jeu.lab.tab_salle[jeu.perso.tag].nb_mob; i++)
                        {
                            if(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i].statue == VIVANT)
                            {
                                if(colision_mob(jeu.lab.tab_salle[jeu.perso.tag].tab_mob[i], jeu.perso))
                                {
                                    mob_cooldown = SDL_GetTicks();
                                    DEBUG_MODE
                                        printf("Le joueur prend 1 degats\n");
                                    jeu.perso.pv--;
                                }
                            }
                        }
                    }

                    switch(jeu.lab.tab_salle[jeu.perso.tag].nb_porte)
                    {
                        case 1:
                            // Si on touche la porte du haut, on passe à la salle suivante et on spawn en bas
                            if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[1], jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                            {
                                jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y) + (jeu.lab.tab_salle[jeu.perso.tag].porte[0].porte.h) / 2;
                                jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle - 1;
                                printf("Salle : %d\n", jeu.perso.tag);

                            }else if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[0], jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                            {   // Si on touche la porte du bas, on passe à la salle précédente et on spawn en haut
                                jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y + jeu.lab.tab_salle[jeu.perso.tag].salle.h ) - (jeu.lab.tab_salle[jeu.perso.tag].porte[1].porte.h)/2 - jeu.perso.perso.h - 5;
                                jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle + 1;
                                printf("Salle : %d\n", jeu.perso.tag);
                            }
                            break;

                        case 2:
                            if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[1], jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[1].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                            {
                                jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y + jeu.lab.tab_salle[jeu.perso.tag].salle.h ) - (jeu.lab.tab_salle[jeu.perso.tag].porte[1].porte.h)/2 - jeu.perso.perso.h;
                                jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle + 1;
                                printf("Salle : %d\n", jeu.perso.tag);

                            }else if((collision_porte(jeu.perso, jeu.lab.tab_salle[jeu.perso.tag].porte[0], jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_entree, jeu.lab.tab_salle[jeu.perso.tag].porte[0].salle_dest) != jeu.lab.tab_salle[jeu.perso.tag].tag_salle) && (jeu.lab.tab_salle[jeu.perso.tag].nb_mob_mort == 5))
                            {   // Si on touche la porte du bas, on passe à la salle précédente et on spawn en haut
                                jeu.perso.perso.y = (jeu.lab.tab_salle[jeu.perso.tag].salle.y) + (jeu.lab.tab_salle[jeu.perso.tag].porte[0].porte.h) / 2;
                                jeu.perso.tag = jeu.lab.tab_salle[jeu.perso.tag].tag_salle - 1;
                                printf("Salle : %d\n", jeu.perso.tag);
                            }
                            break;

                        default:
                            break;
                    }

                    if(jeu.lab.tab_salle[TAILLE_LAB - 1].nb_mob_mort == 5)
                    {
                        nettoyage_ecran(renderer);
                        afficher_texture(renderer, fen, gagner, pos_gagner, plein_ecran, 50, 50, -1, -1);
                        SDL_RenderPresent(renderer);
                        temps_gagner = SDL_GetTicks();
                        while(SDL_GetTicks() - temps_gagner <= 3000);
                        jeu_launched = SDL_FALSE;
                        en_partie = SDL_FALSE;
                        premiere_partie = SDL_TRUE;
                    }
                    if(jeu.perso.pv <= 0)
                    {
                        nettoyage_ecran(renderer);
                        afficher_texture(renderer, fen, mort, pos_mort, plein_ecran, 50, 50, -1, -1);
                        SDL_RenderPresent(renderer);
                        temps_mort = SDL_GetTicks();
                        while(SDL_GetTicks() - temps_mort <= 3000);
                        jeu_launched = SDL_FALSE;
                        en_partie = SDL_FALSE;
                        premiere_partie = SDL_TRUE;
                    }

                    SDL_Delay(10);
                    break;
                }
            }
        }
    }

    free_TabChunk(pistolet, 2);
    free_TabChunk(epee, 4);
    Mix_FreeMusic(main_theme);
    Mix_CloseAudio();
    clean_ressources(fen, renderer, NULL);
    SDL_Quit();
    return EXIT_SUCCESS;
}