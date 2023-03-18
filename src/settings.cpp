#include "Settings.hpp"

bool settings(RenderWindow &window, Game &game){
    // Recursos usados
    SDL_Cursor* cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor* cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    std::vector<Entity> entities = 
    {
        Entity(Vector2f(45,95,870,340),window.tex[GRADE]),
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[VOLTAR]),

        Entity(Vector2f((window.getPos().w-30 - 800)/2,110,30,30),window.tex[MARKBOX]),
        Entity(Vector2f((window.getPos().w-30 - 800 + 90)/2,105,212,36),window.tex[PODERES_BASIC]),

        Entity(Vector2f((window.getPos().w+3 + 15)/2,110,30,30),window.tex[MARKBOX]),
        Entity(Vector2f((window.getPos().w+3 + 15 + 90)/2,105,230,36),window.tex[PODERES_ESPECIAIS]),

        Entity(Vector2f((window.getPos().w-30 - 800)/2,160,30,30),window.tex[ALT_2]),
        Entity(Vector2f((window.getPos().w-30 - 800 + 90)/2,155,230,36),window.tex[VELOCIDADE_START]),

        Entity(Vector2f((window.getPos().w+3 + 15)/2,160,30,30),window.tex[ALT_2]),
        Entity(Vector2f((window.getPos().w+3 + 15 + 90)/2,155,288,36),window.tex[VELOCIDADE_ADD]),

        Entity(Vector2f((window.getPos().w-30 - 800)/2,210,30,30),window.tex[ALT_RANDOM]),
        Entity(Vector2f((window.getPos().w-30 - 800 + 90)/2,205,288,36),window.tex[BALL_DIRECTION]),

        Entity(Vector2f((window.getPos().w-310)/2,2,310,80),window.tex[TITULO_CONFIGURAR])
    };

    // Deixa as Markboxes certas
    if(game.basicPowers) entities[2].setTexture(window.tex[MARKEDBOX]);
    if(game.specialPowers) entities[4].setTexture(window.tex[MARKEDBOX]);
    entities[6].setTexture(window.tex[ALT_RANDOM + game.speed_level]);
    entities[8].setTexture(window.tex[ALT_1 + game.speed_increaser]);
    entities[10].setTexture(window.tex[ALT_RANDOM + game.direction]);

    // Loop
    FPS fps;
    fps.start();
    bool settstate = 1; SDL_Event ev;
    while(settstate){
        fps.update();
        for(int i = 0; i < fps.updateAmount(); i++){
            // Atualizações
            int mousex, mousey;
            SDL_GetMouseState(&mousex,&mousey);

            bool condition_is_in_leave = setarea(entities[1]);
            bool condition_config_1 = setarea(entities[2]);
            bool condition_config_2 = setarea(entities[4]);
            bool condition_alt_velinit = setarea(entities[6]);
            bool condition_alt_veladder = setarea(entities[8]);
            bool condition_alt_dir = setarea(entities[10]);
            
            if(condition_is_in_leave || condition_config_1 || condition_config_2 || condition_alt_veladder || condition_alt_velinit || condition_alt_dir){
                SDL_SetCursor(cursor_hand);
            } else {
                SDL_SetCursor(cursor_arrow);
            }

            while(SDL_PollEvent(&ev)){
                if(ev.type == SDL_QUIT){
                    SDL_SetCursor(cursor_arrow);
                    return 0;
                } else if(ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT){
                    if(condition_is_in_leave){
                        SDL_SetCursor(cursor_arrow);
                        settstate = 0;

                    } else if(condition_config_1){
                        game.basicPowers = !game.basicPowers;
                        if(game.basicPowers){
                            entities[2].setTexture(window.tex[MARKEDBOX]);
                        } else {
                            entities[2].setTexture(window.tex[MARKBOX]);
                        }

                    } else if(condition_config_2){
                        game.specialPowers = !game.specialPowers;
                        if(game.specialPowers){
                            entities[4].setTexture(window.tex[MARKEDBOX]);
                        } else {
                            entities[4].setTexture(window.tex[MARKBOX]);
                        }

                    } else if(condition_alt_velinit){
                        game.speed_level++;
                        if(game.speed_level >= 6){
                            game.speed_level = 0;
                        }
                        entities[6].setTexture(window.tex[ALT_RANDOM + game.speed_level]);

                    } else if(condition_alt_veladder){
                        game.speed_increaser++;
                        if(game.speed_increaser >= 6){
                            game.speed_increaser = 0;
                        }
                        entities[8].setTexture(window.tex[ALT_1 + game.speed_increaser]);

                    } else if(condition_alt_dir){
                        game.direction++;
                        if(game.direction >= 3){
                            game.direction = 0;
                        }
                        entities[10].setTexture(window.tex[ALT_RANDOM + game.direction]);

                    }
                }
            }
            const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
            if (keyboard[SDL_SCANCODE_ESCAPE])
            {
                SDL_SetCursor(cursor_arrow);
                settstate = 0;
            }
        }
        fps.delay();
        // Renderizar e Desenhar
        window.clear();
        for(Entity e : entities){
            window.render(e);
        }
        window.display();
    }
    return 1;
};