#include "jeu.h"


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
                                        perso1.velocite.x = 0;
                                        continue;

                                    case SDLK_d:
                                        perso1.velocite.x = 0;
                                        continue;

                                    case SDLK_s:
                                        perso1.velocite.y = 0;
                                        continue;

                                    case SDLK_z:
                                        perso1.velocite.y = 0;
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
                                        perso1.velocite.x = -VITESSE;
                                        continue;

                                    case SDLK_d:
                                        perso1.velocite.x = VITESSE;
                                        continue;

                                    case SDLK_s:
                                        perso1.velocite.y = VITESSE;
                                        continue;

                                    case SDLK_z:
                                        perso1.velocite.y = -VITESSE;
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
                    }