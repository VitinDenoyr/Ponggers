#include "Admin.hpp"

bool admin(RenderWindow &window, Game &game, Audio &audio){
    // Recursos
    SDL_Cursor* cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor* cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    std::vector<Entity> entities = {
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[VOLTAR]),
        Entity(Vector2f((window.getPos().w-336)/2,5,336,60),window.tex[ADMINLOGO])
        /*
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[TXT_ALTERAR]),
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[ENTSELEC_BOLA]),
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[TXT_PARA]),
        Entity(Vector2f((window.getPos().w-240)/2,462,240,60),window.tex[TEXTBOX_PATH])
        */
    };

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

            if(condition_is_in_leave){
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