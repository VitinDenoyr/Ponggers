#include "Menu.hpp"

bool menu(RenderWindow &window, Game &game, Audio &audio)
{
    // Recursos usados
    SDL_Cursor* cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor* cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    Entity logo(Vector2f(230,50,500,80),window.tex[LOGO]);
    Entity btn_jogar(Vector2f((window.getPos().w - 240.0f)/2,(190),240,60),window.tex[PLAY]);
    Entity btn_config(Vector2f((window.getPos().w - 240.0f)/2,(300),240,60),window.tex[CONFIG]);
    Entity btn_controls(Vector2f((window.getPos().w - 240.0f)/2,(410),240,60),window.tex[CONTROLS]);
    
    // Menu loop
    FPS fps;
    fps.start();
    bool menustate = 1; SDL_Event ev;
    while(menustate)
    {
        fps.update();
        for (int i = 0; i < fps.updateAmount(); i++){
            // Atualizações
            int mousex, mousey;
            SDL_GetMouseState(&mousex,&mousey);

            bool condition_is_in_start = setarea(btn_jogar);
            bool condition_is_in_controls = setarea(btn_controls);
            bool condition_is_in_config = setarea(btn_config);
            
            if(condition_is_in_start || condition_is_in_config || condition_is_in_controls){
                SDL_SetCursor(cursor_hand);
            } else {
                SDL_SetCursor(cursor_arrow);
            }

            while (SDL_PollEvent(&ev)){
                if (ev.type == SDL_QUIT){
                    return 0;
                } else if(ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT){
                    if(condition_is_in_start){
                        SDL_SetCursor(cursor_arrow);
                        return 1;
                    } else if(condition_is_in_config){
                        SDL_SetCursor(cursor_arrow);
                        bool will_play = settings(window,game); //Vai para as configurações
                        if(!will_play) return 0;
                    } else if(condition_is_in_controls){
                        SDL_SetCursor(cursor_arrow);
                        bool will_play = controls(window);
                        if(!will_play) return 0;
                    }
                }
            }
        }

        fps.delay();

        // Renderizar e desenhar
        window.clear();
        window.render(logo);
        window.render(btn_jogar);
        window.render(btn_config);
        window.render(btn_controls);
        window.display();
    }
    return 1;
}