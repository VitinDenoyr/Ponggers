#include "Pong.hpp"

bool pong(RenderWindow &window, Game &game, Audio &audio)
{
    // Recursos usados
    Ball e_Ball(Vector2f((window.getPos().w - 16)/2,(440 - 16)/2, 16, 16),window.tex[BALL_W]);
    Paddle e_Player1(Vector2f(33,(440 - 100)/2, 10, 100),window.tex[PADDLE_1]);
    Paddle e_Player2(Vector2f(window.getPos().w - 45,(440 - 100)/2, 10, 100),window.tex[PADDLE_2]);
    std::vector<Entity> entities =
    {
        Entity(Vector2f((window.getPos().w - 36 - 70)/2, 10, 36 , 60),window.tex[SCORE1]),
        Entity(Vector2f((window.getPos().w - 36 + 70)/2, 10, 36 , 60),window.tex[SCORE2]),
        Entity(Vector2f((window.getPos().w - 10)/2, 10, 12, 60),window.tex[SEPARATOR])
    };

    // Loop
    bool quit = false;
    FPS fps;
    fps.start();

    game.reset(e_Ball,e_Player1,e_Player2);
    game.score[0] = 0; game.score[1] = 0; e_Player1.setspeed(game.player_speed); e_Player2.setspeed(game.player_speed);
    int oldscore[2] = {0,0}; window.scoreUpdate(0,0,entities[0],entities[1]);

    int spawntime = 0; int spawnlimit = 120*14; bool boxtype = 0;

    if(!game.basicPowers && game.specialPowers) boxtype = 1;

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
            if (keyboard[SDL_SCANCODE_SPACE] && !game.hasLaunched){
                game.start(e_Ball);
            }
            if(game.hasLaunched){ // Movimenta jogadores
                if(keyboard[SDL_SCANCODE_W])
                {
                    e_Player1.move(-1);
                }
                if(keyboard[SDL_SCANCODE_S])
                {
                    e_Player1.move(1);
                }
                int adminMoving = 0;
                if(game.adminMove){
                    if(keyboard[SDL_SCANCODE_F])
                    {
                        e_Ball.getPos().x -= 5;
                        adminMoving = 1;
                    }
                    if(keyboard[SDL_SCANCODE_H])
                    {
                        e_Ball.getPos().x += 5;
                        adminMoving = 1;
                    }
                    if(keyboard[SDL_SCANCODE_T])
                    {
                        e_Ball.getPos().y -= 5;
                        adminMoving = 1;
                    }
                    if(keyboard[SDL_SCANCODE_G])
                    {
                        e_Ball.getPos().y += 5;
                        adminMoving = 1;
                    }
                }
                if(game.use_ia){
                    Ball* closerBall = &e_Ball;
                    if(closerBall->getxs() < 0){
                        if(e_Player2.getPos().y > (window.getPos().h - e_Player2.getPos().h)/2){
                            e_Player2.move(-1);
                        } else if(e_Player2.getPos().y < (window.getPos().h - e_Player2.getPos().h)/2-game.player_speed) {
                            e_Player2.move(1);
                        }
                    } else {
                        if((closerBall->getPos().y + 8) > (e_Player2.getPos().y+e_Player2.getPos().h/2)){
                            e_Player2.move(1);
                        } else if((closerBall->getPos().y + 8) < (e_Player2.getPos().y+e_Player2.getPos().h/2-game.player_speed)) {
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
                bool madePoint = 0;
                if(!adminMoving) madePoint = game.moveBall(e_Ball,e_Player1,e_Player2);
                if(game.basicPowers || game.specialPowers){ // poderes
                    spawntime++;
                    game.powerMovement(e_Ball,e_Player1,e_Player2);
                    if(spawntime >= spawnlimit){
                        spawntime = 0;
                        if(game.powers.size() == 0){
                            game.addPower(boxtype);
                            if(game.basicPowers && game.specialPowers){
                                int rng = (SDL_GetTicks64()%113);
                                if(rng%2 == 0){
                                    boxtype = 0;
                                } else {
                                    boxtype = 1;
                                }
                            }
                        }
                    }
                }
                if(madePoint){
                    spawntime = 0;
                    int win = game.reset(e_Ball,e_Player1,e_Player2);
                    if(win > 0){
                        audio.playMusic(MUSIC_Victory,999);
                        quit = !(winner(window,audio,win));
                        audio.stopMusic();
                        return !quit;
                    }
                }
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
        for(Power p : game.powers){
            if(!p.active){
                window.render(p);
            } else if (p.powerId == SPOW_MIDWALL){
                for(Entity* e : p.positions){
                    window.render(*e);
                }
            }
        }
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