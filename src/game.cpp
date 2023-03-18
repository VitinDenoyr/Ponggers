#include "Game.hpp"

void Game::reset(Ball &p_Ball, Paddle &p_p1, Paddle &p_p2){
    p_Ball.mid(); p_p1.mid(); p_p2.mid();
    hasLaunched = 0;
}

bool Game::gamestate(){
    return hasLaunched;
}

void Game::start(Ball &p_ball){
    float strt_spd[6] = {1.0f, 1.25f, 2.10f, 3.00f, 4.10f, 5.25f};
    float strt_dir[3] = {1,1,-1};
    hasLaunched = 1;
    p_ball.setspeed((strt_dir[direction])*(strt_spd[speed_level]*1.25f),0.05f);
}

void Game::moveBall(Ball &p_ball, Paddle& p_p1, Paddle& p_p2)
{
    p_ball.getPos().x += p_ball.getxs();
    p_ball.getPos().y += p_ball.getys();
    // Condições de colisão
    bool cdt_passed_p2 = p_ball.getPos().x - p_ball.getxs() < 899 && p_ball.getPos().x >= 899;
    bool cdt_passed_p1 = p_ball.getPos().x - p_ball.getxs() > 45 && p_ball.getPos().x <= 45;
    bool cdt_fronts_p2 = p_ball.getPos().y+16 >= p_p2.getPos().y && p_ball.getPos().y <= p_p2.getPos().y+p_p2.getPos().h;
    bool cdt_fronts_p1 = p_ball.getPos().y+16 >= p_p1.getPos().y && p_ball.getPos().y <= p_p1.getPos().y+p_p1.getPos().h;
    float spi[6] = {1.02f, 1.04f, 1.06f, 1.09f, 1.13f, 1.00f};
    if(cdt_passed_p1){ 
        if(cdt_fronts_p1){ 
            audio.playSound(SOUND_Collision,0);
            p_ball.getPos().x = 46;
            p_ball.getxs() *= -1 * spi[speed_increaser];
            if(std::abs(p_ball.getxs()) <= 60){
                //
            }
            if(std::abs(p_ball.getys()) <= 60){
                float curvefactor = std::abs(p_ball.getxs())*(p_ball.getPos().y - p_p1.getPos().y - 42.0f)/180.0f;
                p_ball.getys() += curvefactor;
            }
        }
    } else if(cdt_passed_p2){
        if(cdt_fronts_p2){
            audio.playSound(SOUND_Collision,0);
            p_ball.getPos().x = 898;
            p_ball.getxs() *= -1 * spi[speed_increaser];
            if(std::abs(p_ball.getxs()) <= 60){
                //
            }
            if(std::abs(p_ball.getys()) <= 75){
                float curvefactor = std::abs(p_ball.getxs())*(p_ball.getPos().y - p_p2.getPos().y - 42.0f)/180.0f;
                p_ball.getys() += curvefactor;
            }
        }
    }
    if(p_ball.getPos().y < 0){
        audio.playSound(SOUND_Collision,0);
        p_ball.getPos().y = 0 + (0 - p_ball.getPos().y);
        p_ball.getys() *= -1;
    } else if(p_ball.getPos().y > 524){
        audio.playSound(SOUND_Collision,0);
        p_ball.getPos().y = 524 - (p_ball.getPos().y - 524);
        p_ball.getys() *= -1;
    }
    if(p_ball.getPos().x > 944){
        reset(p_ball, p_p1, p_p2);
        score[0]++;
        audio.playSound(SOUND_Point,0);
    } else if(p_ball.getPos().x < 0){
        reset(p_ball, p_p1, p_p2);
        score[1]++;
        audio.playSound(SOUND_Point,0);
    }
}