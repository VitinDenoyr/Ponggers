#include "Pong.hpp"

bool pong(RenderWindow &window, Game &game, Audio &audio)
{
    // Recursos usados
    Ball e_Ball(Vector2f((window.getPos().w - 16)/2,(window.getPos().h - 16)/2, 16, 16),window.tex[BALL_W]);
    Paddle e_Player1(Vector2f(33,(window.getPos().h - 100)/2, 10, 100),window.tex[PADDLE_1]);
    Paddle e_Player2(Vector2f(window.getPos().w - 45,(window.getPos().h - 100)/2, 10, 100),window.tex[PADDLE_2]);
    std::vector<Entity> entities =
    {
        Entity(Vector2f((window.getPos().w - 36 - 70)/2, 10, 36 , 60),window.tex[SCORE1]),
        Entity(Vector2f((window.getPos().w - 36 + 70)/2, 10, 36 , 60),window.tex[SCORE2]),
        Entity(Vector2f((window.getPos().w - 10)/2, 10, 12, 60),window.tex[SEPARATOR])
    };

    // Loop
    FPS fps;
    fps.start();

    game.reset(e_Ball,e_Player1,e_Player2);
    game.score[0] = 0; game.score[1] = 0; e_Player1.setspeed(game.player_speed); e_Player2.setspeed(game.player_speed);
    int oldscore[2] = {0,0}; window.scoreUpdate(0,0,entities[0],entities[1]);

    bool gamestate = 1; SDL_Event ev;
    while(gamestate){
        fps.update();
        for(int i = 0; i < fps.updateAmount(); i++){
            // Atualizações
            while (SDL_PollEvent(&ev)){
                if (ev.type == SDL_QUIT) {
                    return 0;
                }
            }
            const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
            if (keyboard[SDL_SCANCODE_ESCAPE])
            {
                gamestate = 0;
            }
            if (keyboard[SDL_SCANCODE_SPACE] && !game.gamestate()){
                game.start(e_Ball);
            }
            if(game.gamestate()){ // Movimenta jogadores
                if (keyboard[SDL_SCANCODE_W])
                {
                    e_Player1.move(-1);
                }
                if (keyboard[SDL_SCANCODE_S])
                {
                    e_Player1.move(1);
                }
                if(game.use_ia){
                    Ball* closerBall = &e_Ball;
                    if(closerBall->getxs() < 0){
                        if(e_Player2.getPos().y > 220){
                            e_Player2.move(-1);
                        } else if(e_Player2.getPos().y < 220-game.player_speed) {
                            e_Player2.move(1);
                        }
                    } else {
                        if((closerBall->getPos().y + 8) > (e_Player2.getPos().y+50)){
                            e_Player2.move(1);
                        } else if((closerBall->getPos().y + 8) < (e_Player2.getPos().y+50-game.player_speed)) {
                            e_Player2.move(-1);
                        }
                    }
                } else {
                    if (keyboard[SDL_SCANCODE_UP])
                    {
                        e_Player2.move(-1);
                    }
                    if (keyboard[SDL_SCANCODE_DOWN])
                    {
                        e_Player2.move(1);
                    }
                }
                game.moveBall(e_Ball,e_Player1,e_Player2);

            }
        }
        fps.delay();
        
        // Atualizar score
        if(oldscore[0] != game.score[0] || oldscore[1] != game.score[1]){
            window.scoreUpdate(game.score[0],game.score[1],entities[0],entities[1]);
            oldscore[0] = game.score[0];
            oldscore[1] = game.score[1];
        }

        // Renderizar e Desenhar
        window.clear();
        for(Entity e : entities){
            window.render(e);
        }
        window.render(e_Ball);
        window.render(e_Player1);
        window.render(e_Player2);
        window.display();
    }
    return 1;
}