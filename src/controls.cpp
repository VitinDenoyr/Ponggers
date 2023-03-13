#include "Controls.hpp"

bool controls(RenderWindow &window){
    //Recursos usados
    TTF_Font* font = TTF_OpenFont("res/fonts/Peepo.ttf", 36);
    SDL_Color color_white = {255,255,255,0};
    std::vector<SDL_Surface*> surface_vec = {
        TTF_RenderText_Solid(font,"Controles",color_white),
        TTF_RenderText_Solid(font,"Mover jogador 1",color_white),
        TTF_RenderText_Solid(font,"Mover jogador 2",color_white),
        TTF_RenderText_Solid(font,"Ativar movimento da bola",color_white),
        TTF_RenderText_Solid(font,"Voltar ao menu principal",color_white)
    };
    std::vector<SDL_Rect> rect_vec = {
        {(window.getSize().w-280)/2,2,280,80},
        {(window.getSize().w-180)/2,112,290,50},
        {(window.getSize().w-180)/2,197,290,50},
        {(window.getSize().w-286)/2,282,396,50},
        {(window.getSize().w-320)/2,367,396,50}
    };
    std::vector<Entity> border_vec = {
        Entity(Vector2f((window.getSize().w-455)/2,112,455,60),window.loadTexture("res/images/controls/w_s.png")),
        Entity(Vector2f((window.getSize().w-455)/2,197,455,60),window.loadTexture("res/images/controls/up_down.png")),
        Entity(Vector2f((window.getSize().w-561)/2,282,561,60),window.loadTexture("res/images/controls/spacebar.png")),
        Entity(Vector2f((window.getSize().w-502)/2,367,502,60),window.loadTexture("res/images/controls/esc.png")),
        Entity(Vector2f((window.getSize().w-240)/2,462,240,60),window.loadTexture("res/images/buttons/button_return.png"))
    };
    
    //Loop
    bool confstate = 1; SDL_Event ev;
    long double frameDuration = 1000.0f/120.0f;
    long double lastFrame = 0, currentFrame = SDL_GetTicks64();
    while(confstate){
        // Controle de frames
        lastFrame = currentFrame;
        currentFrame = SDL_GetTicks64();
        long double superior_frame_amount = std::ceil((currentFrame - lastFrame + 1) / frameDuration);
        long double superior_remainder = (superior_frame_amount * (frameDuration) - (currentFrame - lastFrame));
        for (int i = 0; i < superior_frame_amount; i++){
            // Atualizações
            int mousex, mousey;
            SDL_GetMouseState(&mousex,&mousey);
            bool condition_is_in_config = mousex >= border_vec[4].getPos().x && mousey >= border_vec[4].getPos().y && mousex <= border_vec[4].getPos().x+border_vec[4].getPos().w && mousey <= border_vec[4].getPos().y+border_vec[4].getPos().h;
            if(condition_is_in_config){
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
            } else {
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
            }
            while(SDL_PollEvent(&ev)){
                if(ev.type == SDL_QUIT){
                    return 0;
                } else if(ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT){
                    if(condition_is_in_config){
                        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
                        confstate = 0;
                    }
                }
            }
        }
        float delayTime = std::max(0, (int)std::floor(superior_remainder - (SDL_GetTicks64() - currentFrame))); // Completar as operações anteriores - tempo ja gasto
        SDL_Delay(delayTime);
        currentFrame = SDL_GetTicks64();

        // Renderizar e Desenhar
        window.clear();
        for(int i = 0; i < rect_vec.size(); i++){
            window.render(surface_vec[i],rect_vec[i]);
            window.render(border_vec[i]);
        }
        window.display();
    }
    return 1;
}