#include "Settings.hpp"

bool settings(RenderWindow &window){
    //Recursos usados
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
            while(SDL_PollEvent(&ev)){
                if(ev.type == SDL_QUIT){
                    return 0;
                } else if(ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_RIGHT){
                    confstate = 0;
                }
            }
            const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
            if (keyboard[SDL_SCANCODE_ESCAPE])
            {
                confstate = 0;
            }
        }
        float delayTime = std::max(0, (int)std::floor(superior_remainder - (SDL_GetTicks64() - currentFrame))); // Completar as operações anteriores - tempo ja gasto
        SDL_Delay(delayTime);
        currentFrame = SDL_GetTicks64();

        // Renderizar e Desenhar
        window.clear();

        window.display();
    }
    return 1;
}