#include <Main.hpp>

int main(int argc, char **argv)
{
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) FAIL_SDL)
    {
        std::cout << "Falha na inicialização do SDL. Erro: " << SDL_GetError() << std::endl;
    }
    if (IMG_Init(IMG_INIT_PNG) FAIL_IMG)
    {
        std::cout << "Falha na inicialização do SDL_Image. Erro: " << SDL_GetError() << std::endl;
    }
    if (TTF_Init() FAIL_TTF)
    {
        std::cout << "Falha na inicialização do SDL_Ttf. Erro: " << SDL_GetError() << std::endl;
    }
    if (Mix_Init(MIX_INIT_MP3) FAIL_MIX || Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,2048) < 0)
    {
        std::cout << "Falha na inicialização do SDL_Mixer. Erro: " << SDL_GetError() << std::endl;
    }

    // Carregar recursos
    bool runstate = true;
    SDL_Color color_white = {255,255,255,0};
    RenderWindow window("Ponggers",960,540);

    // Loop
    while(runstate)
    {
        runstate = menu(window);
        if(runstate){ 
            runstate = pong(window);
        }
    }

    // Encerramento
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}