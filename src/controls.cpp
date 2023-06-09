#include "Controls.hpp"

bool controls(RenderWindow &window, Audio &audio){
    //Recursos usados
    SDL_Cursor* cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor* cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    std::vector<Entity> entities = {
        Entity(Vector2f((window.getPos().w-280)/2,2,280,80),window.tex[TITULO_CONTROLES]),
        Entity(Vector2f((window.getPos().w-180)/2,112,290,50),window.tex[TXT_MOVE1]),
        Entity(Vector2f((window.getPos().w-180)/2,197,290,50),window.tex[TXT_MOVE2]),
        Entity(Vector2f((window.getPos().w-286)/2,282,396,50),window.tex[TXT_ATIVABOLA]),
        Entity(Vector2f((window.getPos().w-320)/2,367,396,50),window.tex[TXT_VOLTARAOMENU]),
        Entity(Vector2f((window.getPos().w-455)/2,112,455,60),window.tex[BORDA_MOVE1]),
        Entity(Vector2f((window.getPos().w-455)/2,197,455,60),window.tex[BORDA_MOVE2]),
        Entity(Vector2f((window.getPos().w-561)/2,282,561,60),window.tex[BORDA_ATIVABOLA]),
        Entity(Vector2f((window.getPos().w-502)/2,367,502,60),window.tex[BORDA_VOLTARAOMENU]),
        Entity(Vector2f((window.getPos().w-155)/2,462,155,60),window.tex[VOLTAR])
    };
    
    // Loop
    FPS fps;
    fps.start();
    bool contstate = 1; SDL_Event ev;
    while(contstate){
        // Controle de frames
        fps.update();
        for(int i = 0; i < fps.updateAmount(); i++){
            // Atualizações
            int mousex, mousey;
            SDL_GetMouseState(&mousex,&mousey);

            bool condition_is_in_leave = setarea(entities[9]);
            
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
                        contstate = 0;
                    }
                }
            }
            const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
            if (keyboard[SDL_SCANCODE_ESCAPE])
            {
                SDL_SetCursor(cursor_arrow);
                contstate = 0;
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
}