#include "Pong.hpp"

bool pong(RenderWindow &window){
    // Recursos usados

    // Loop
    FPS fps;
    fps.start();
    bool gamestate = 1; SDL_Event ev;
    while(gamestate){
        fps.update();
        for(int i = 0; i < fps.updateAmount(); i++){
            //Update
            while (SDL_PollEvent(&ev)){
                if (ev.type == SDL_QUIT) {
                    return 0;
                }
            }
        }
        fps.delay();
        return 1;
    }
    return 1;
}