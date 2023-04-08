#include "Admin.hpp"

bool admin(RenderWindow &window, Game &game, Audio &audio){
    // Recursos
    SDL_Cursor* cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor* cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    std::vector<Entity> entities = {
        Entity(Vector2f((window.getPos().w-155)/2,462,155,60),window.tex[VOLTAR]),
        Entity(Vector2f((window.getPos().w-336)/2,5,336,60),window.tex[ADMINLOGO]),
        Entity(Vector2f((window.getPos().w-650)/2,72,230,60),window.tex[ADM_MOVEBALL]),
        Entity(Vector2f((window.getPos().w+115)/2,72,305,60),window.tex[ADM_SECRETBG])
        /*
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[TXT_ALTERAR]),
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[ENTSELEC_BOLA]),
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[TXT_PARA]),
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[TEXTBOX_PATH])
        */
    };
    // Corrigir texturas
    if(game.adminMove) entities[2].setTexture(window.tex[ADM_MOVEBALL2]);

    // Loop
    FPS fps;
    fps.start();
    bool admloop = 1; SDL_Event ev;
    while(admloop){
        // Controle de frames
        fps.update();
        for(int i = 0; i < fps.updateAmount(); i++){
            //Atualizações
            int mousex, mousey;
            SDL_GetMouseState(&mousex,&mousey);

            bool condition_is_in_leave = setarea(entities[0]);
            bool condition_is_in_moveball = setarea(entities[2]);

            if(condition_is_in_leave || condition_is_in_moveball){
                SDL_SetCursor(cursor_hand);
            } else {
                SDL_SetCursor(cursor_arrow);
            }

            while(SDL_PollEvent(&ev)){
                if(ev.type == SDL_QUIT){
                    return 0;
                } else if(ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT){
                    if(condition_is_in_leave){
                        audio.playSound(SOUND_Click,0,1);
                        SDL_SetCursor(cursor_arrow);
                        return 1;
                    } else if(condition_is_in_moveball){
                        if(game.adminMove == 1){
                            entities[2].setTexture(window.tex[ADM_MOVEBALL]);
                            game.adminMove = 0;
                        } else {
                            entities[2].setTexture(window.tex[ADM_MOVEBALL2]);
                            game.adminMove = 1;
                        }
                    }
                }
            }
            
        }
        fps.delay();
        window.clear();
        for(Entity e : entities){
            window.render(e);
        }
        window.display();
    }
    return 1;
}

// Para funcionar corretamente:
/*
- Todos os arquivos usados devem estar em uma subpasta com nome "admin"
- Arquivos de fundo secreto: "background(K).png", onde (K) deve ser substituido por um número de 1 á 5. Pode-se usar até 5 fundos customizados ao mesmo tempo.

*/

