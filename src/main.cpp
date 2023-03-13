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

    // Criar janela principal e classe de configurações do jogo
    RenderWindow window("Ponggers", SCREENWIDTH, SCREENHEIGHT);

    // Carregar Recursos Usados (Menu + Jogo)
    bool runstate = true;
    TTF_Font *font = TTF_OpenFont("res/fonts/Peepo.ttf", 36);
    SDL_Color color_white = {255,255,255,0};
    if(font == NULL){
        std::cout << "Falha no carregamento da fonte."<< std::endl;
    }

    // Menu
    Game game(SCREENWIDTH, SCREENHEIGHT, window);
    while(runstate){
        runstate = menu(window,game);
        if(runstate){ //Se o menu retornar que foi clicado em jogar, cria um jogo
            runstate = pong(window, game); //Decide se o jogo termina aqui ou volta pro menu
        }
    }

    // Encerramento
    window.memoryClear();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}