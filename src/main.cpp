#include "Main.hpp"

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
    std::vector<const char*> musics = {
        "res/sounds/victory.mp3",
        "res/sounds/admin.mp3"
    };
    std::vector<const char*> sounds = {
        "res/sounds/collision.wav",
        "res/sounds/point.wav",
        "res/sounds/click.wav"
    };
    Audio audio(100,sounds,musics);
    Game game(audio, window);
    // Loop
    while(runstate)
    {
        runstate = menu(window,game,audio);
        if(runstate){ 
            runstate = pong(window,game,audio);
        }
    }
    // Encerramento
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    exit(0);
    return 0;
}