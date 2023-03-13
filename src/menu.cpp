#include "Menu.hpp"

bool menu(RenderWindow &window, Game &game)
{
    // Recursos usados
    TTF_Font* font = TTF_OpenFont("res/fonts/Peepo.ttf", 36);
    // -logo
    int logo_w = 500, logo_h = 80;
    SDL_Color logo_color = {205, 215, 255, 0};
    SDL_Rect logo_pos = {(window.getSize().w - logo_w)/2,(50),(logo_w),(logo_h)};
    SDL_Surface* logo_surface = TTF_RenderText_Solid(font,"P O N G G E R S",logo_color);
    int division_space = (window.getSize().h - logo_pos.y + logo_pos.h)/7;
    // -botao jogar
    SDL_Texture* btn_jogar_texture = window.loadTexture("res/images/buttons/button_play.png");
    Entity btn_jogar(Vector2f((window.getSize().w - 240)/2,(190),240,60),btn_jogar_texture);
    // -botao config
    SDL_Texture* btn_config_texture = window.loadTexture("res/images/buttons/button_config.png");
    Entity btn_config(Vector2f((window.getSize().w - 240)/2,(300),240,60),btn_config_texture);
    // -botao controles
    SDL_Texture* btn_controls_texture = window.loadTexture("res/images/buttons/button_controls.png");
    Entity btn_controls(Vector2f((window.getSize().w - 240)/2,(410),240,60),btn_controls_texture);
    
    // Menu loop
    long double frameDuration = 1000.0f / 120.0f;
    long double lastFrame = 0, currentFrame = SDL_GetTicks64();
    bool menustate = 1; SDL_Event ev; int r = 0;
    while(menustate)
    {
        // Controle de frames
        lastFrame = currentFrame;
        currentFrame = SDL_GetTicks64();
        long double superior_frame_amount = std::ceil((currentFrame - lastFrame + 1) / frameDuration);
        long double superior_remainder = (superior_frame_amount * (frameDuration) - (currentFrame - lastFrame));
        for (int i = 0; i < superior_frame_amount; i++){
            // Atualizações
            int mousex, mousey;
            SDL_GetMouseState(&mousex,&mousey);
            bool condition_is_in_start = mousex >= btn_jogar.getPos().x && mousey >= btn_jogar.getPos().y && mousex <= btn_jogar.getPos().x+btn_jogar.getPos().w && mousey <= btn_jogar.getPos().y+btn_jogar.getPos().h;
            bool condition_is_in_controls = mousex >= btn_controls.getPos().x && mousey >= btn_controls.getPos().y && mousex <= btn_controls.getPos().x+btn_controls.getPos().w && mousey <= btn_controls.getPos().y+btn_controls.getPos().h;
            bool condition_is_in_config = mousex >= btn_config.getPos().x && mousey >= btn_config.getPos().y && mousex <= btn_config.getPos().x+btn_config.getPos().w && mousey <= btn_config.getPos().y+btn_config.getPos().h;
            if(condition_is_in_start || condition_is_in_config || condition_is_in_controls){
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
            } else {
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
            }
            while (SDL_PollEvent(&ev)){
                if (ev.type == SDL_QUIT){
                    return 0;
                } else if(ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT){
                    if(condition_is_in_start){
                        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
                        return 1;
                    } else if(condition_is_in_config){
                        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
                        bool will_play = settings(window); //Vai para as configurações
                        if(!will_play) return 0;
                    } else if(condition_is_in_controls){
                        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
                        bool will_play = controls(window);
                        if(!will_play) return 0;
                    }
                }
            }
        }
        float delayTime = std::max(0, (int)std::floor(superior_remainder - (SDL_GetTicks64() - currentFrame))); // Completar as operações anteriores - tempo ja gasto
        SDL_Delay(delayTime);
        currentFrame = SDL_GetTicks64();

        // Renderizar e desenhar
        window.clear();
        window.render(logo_surface,logo_pos);
        window.render(btn_jogar);
        window.render(btn_config);
        window.render(btn_controls);
        window.display();
    }
    return 1;
}