#include "Ingame.hpp"

std::pair<int, int> Game::getScores(){
    return {score[1],score[2]};
}

void Game::Reset(Ball &p_ball, Paddle &p_p1, Paddle &p_p2){
    score[1] = 0; score[2] = 0;
    ball_active = false;
    p_ball.setxs(0); p_ball.setys(0);
    p_ball.ballIteration(((SCREENWIDTH - p_ball.getPos().w)/2 - p_ball.getPos().x),((SCREENHEIGHT - p_ball.getPos().h)/2 - p_ball.getPos().y));
    SDL_Texture* txtr_Ball = window.loadTexture("res/images/pong/ball.png");
    p_ball = Ball(p_ball,txtr_Ball);
    p_p1.middle(); p_p2.middle();
}

void Game::Launch(Ball& p_ball) {
    if(!ball_active){
        ball_active = true;
        p_ball.setxs(3.5);
        p_ball.setys(0.1);
    }
}

void Game::Point(int p_player, Ball& p_ball, Paddle& p_p1, Paddle& p_p2) {
    score[p_player]++;
    p_ball.setxs(0); p_ball.setys(0);
    ball_active = false;
    p_ball.ballIteration(((SCREENWIDTH - p_ball.getPos().w)/2 - p_ball.getPos().x),((SCREENHEIGHT - p_ball.getPos().h)/2 - p_ball.getPos().y)); //goto mid
    p_p1.middle(); p_p2.middle(); //players go to mid
    SDL_Texture* txtr_Ball = window.loadTexture("res/images/pong/ball.png");
    p_ball = Ball(p_ball,txtr_Ball);
}


void Game::MoveBall(Ball& p_ball, Paddle& p_p1, Paddle& p_p2){
    //Movimenta
    p_ball.ballIteration(p_ball.xs(),p_ball.ys());

    //Condições
    bool condition_ball_touch_floor = (p_ball.getPos().y > 524);
    bool condition_ball_touch_ceil = (p_ball.getPos().y < 0);
    bool condition_ball_in_pad_height_p1 = (p_ball.getPos().y - p_p1.getPos().y) > -16 && (p_ball.getPos().y - p_p1.getPos().y) < 100;
    bool condition_ball_in_pad_height_p2 = (p_ball.getPos().y - p_p2.getPos().y) > -16 && (p_ball.getPos().y - p_p2.getPos().y) < 100;
    bool condition_ball_touch_p1 = (p_ball.getPos().x - p_ball.xs() > p_p1.getPos().w + 25) && (p_ball.getPos().x <= p_p1.getPos().w + 25);
    bool condition_ball_touch_p2 = (p_ball.getPos().x + 16 - p_ball.xs() < (p_p2.getPos().x)) && (p_ball.getPos().x + 16 >= (p_p2.getPos().x));
    bool condition_ball_pass_p1 = p_ball.getPos().x <= 0;
    bool condition_ball_pass_p2 = p_ball.getPos().x >= 944;

    //Detecta colisões e pontos
    if(condition_ball_touch_ceil){ 
        p_ball.ballIteration(0,2*(0-p_ball.getPos().y));
        p_ball.setys(-1*p_ball.ys());
    } else if(condition_ball_touch_floor){ 
        p_ball.ballIteration(0,2*(524-p_ball.getPos().y));
        p_ball.setys(-1*p_ball.ys());
    }

    if(condition_ball_touch_p1 && condition_ball_in_pad_height_p1){ //p1 reflete
        if(std::abs(p_ball.xs()) < 100.0f/1.035f){
            p_ball.setxs(p_ball.xs() * -1.025);
        } else {
            p_ball.setxs(p_ball.xs() * -1);
        }
        p_ball.ballIteration(2*(25+p_p1.getPos().w - p_ball.getPos().x),0);
        double curve_factor = std::abs(p_ball.xs())*(p_ball.getPos().y - p_p1.getPos().y - 42.0f)/180.0f; //Mudar trajetória com base no local do impacto
        p_ball.setys(p_ball.ys()+curve_factor);
        SDL_Texture* txtr_Ball = window.loadTexture("res/images/pong/ball_blue.png");
        p_ball = Ball(p_ball,txtr_Ball);

    } else if(condition_ball_pass_p1){
        Point(2,p_ball,p_p1,p_p2);

    } else if(condition_ball_touch_p2 && condition_ball_in_pad_height_p2){ //p2 reflete
        if(std::abs(p_ball.xs()) < 100.0f/1.035f){
            p_ball.setxs(p_ball.xs() * -1.025);
        } else {
            p_ball.setxs(p_ball.xs() * -1);
        }
        p_ball.ballIteration(2*(p_p2.getPos().x - p_ball.getPos().x - 16),0);
        double curve_factor = std::abs(p_ball.xs())*(p_ball.getPos().y - p_p2.getPos().y - 42.0f)/180.0f; //Trajetória p/ p2
        p_ball.setys(p_ball.ys()+curve_factor);
        SDL_Texture* txtr_Ball = window.loadTexture("res/images/pong/ball_red.png");
        p_ball = Ball(p_ball,txtr_Ball);

    } else if(condition_ball_pass_p2){
        Point(1,p_ball,p_p1,p_p2);

    }
}