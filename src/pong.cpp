#include "Pong.hpp"

bool pong(RenderWindow &window, Game &game){
    // Carregar Recursos Usados (Somente Jogo)
    bool runstate = 1;
    TTF_Font *font = TTF_OpenFont("res/fonts/Peepo.ttf", 36);
    SDL_Color color_white = {255,255,255,0};
    SDL_Texture *txtr_Ball = window.loadTexture("res/images/pong/ball.png");
    SDL_Texture *txtr_Player1 = window.loadTexture("res/images/pong/player_1.png");
    SDL_Texture *txtr_Player2 = window.loadTexture("res/images/pong/player_2.png");

    // Criar Entidades
    Ball ent_Ball(Vector2f((SCREENWIDTH - 16) / 2, (SCREENHEIGHT - 16) / 2, 16, 16), txtr_Ball);
    std::vector<Paddle> ent_Paddle = {
        Paddle(Vector2f(25, (SCREENHEIGHT - 100) / 2, 20, 100), txtr_Player1),
        Paddle(Vector2f(SCREENWIDTH - 45, (SCREENHEIGHT - 100) / 2, 20, 100), txtr_Player2)
    };
    
    // Gameloop
    game.Reset(ent_Ball,ent_Paddle[0],ent_Paddle[1]);
    SDL_Event ev;
    long double frameDuration = 1000.0f / 120.0f;
    long double lastFrame = 0, currentFrame = SDL_GetTicks64();
    while (runstate)
    {
        // Controle de frames
        lastFrame = currentFrame;
        currentFrame = SDL_GetTicks64(); // Atualiza tempo de frame anterior e atual
        long double superior_frame_amount = std::ceil((currentFrame - lastFrame + 1) / frameDuration);
        long double superior_remainder = (superior_frame_amount * (frameDuration) - (currentFrame - lastFrame));
        for (int i = 0; i < superior_frame_amount; i++){ // Conta quantos frames deveriam ter se passado no tempo atual e faz as atualizações
            // Detectar input
            while (SDL_PollEvent(&ev)){
                if (ev.type == SDL_QUIT){
                    runstate = false;
                }
            }
            const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
            // P1
            if (keyboard[SDL_SCANCODE_ESCAPE])
            {
                return 1;
            }
            if (keyboard[SDL_SCANCODE_W])
            {
                ent_Paddle[0].moveUp();
            }
            if (keyboard[SDL_SCANCODE_S])
            {
                ent_Paddle[0].moveDown();
            }
            // P2
            if (keyboard[SDL_SCANCODE_UP])
            {
                ent_Paddle[1].moveUp();
            }
            if (keyboard[SDL_SCANCODE_DOWN])
            {
                ent_Paddle[1].moveDown();
            }
            // Start
            if (keyboard[SDL_SCANCODE_SPACE])
            {
                game.Launch(ent_Ball);
            }
            //Movimenta bola
            game.MoveBall(ent_Ball, ent_Paddle[0], ent_Paddle[1]);
        }
        float delayTime = std::max(0, (int)std::floor(superior_remainder - (SDL_GetTicks64() - currentFrame))); // Completar as operações anteriores - tempo ja gasto
        SDL_Delay(delayTime);
        currentFrame = SDL_GetTicks64();

        // Atualizar dados do placar
        std::stringstream txt_s1; txt_s1 << game.getScores().first;
        SDL_Surface* surface_s1 = TTF_RenderText_Solid(font, txt_s1.str().c_str(), color_white);
        SDL_Rect scrbd_s1 = {(SCREENWIDTH - 36 - 70 - 72*(int)(txt_s1.str().length()-1))/2, 10, 36*(int)(txt_s1.str().length()) , 60};
        std::stringstream txt_s2; txt_s2 << game.getScores().second;
        SDL_Surface* surface_s2 = TTF_RenderText_Solid(font, txt_s2.str().c_str(), color_white);
        SDL_Rect scrbd_s2 = {(SCREENWIDTH - 36 + 70)/2, 10, 36*(int)(txt_s2.str().length()) , 60};
        const char* txt_separator = ":";
        SDL_Surface* surface_separator = TTF_RenderText_Solid(font, txt_separator, color_white);
        SDL_Rect scrbd_separator = {(SCREENWIDTH - 10)/2, 10, 12 , 60};

        // Renderizar e Desenhar
        window.clear();
        window.render(surface_s1, scrbd_s1);
        window.render(surface_s2, scrbd_s2);
        window.render(surface_separator, scrbd_separator);
        window.render(ent_Ball);
        for (Paddle &ent : ent_Paddle){
            window.render(ent);
        }
        window.display();
    }
    return runstate;
}