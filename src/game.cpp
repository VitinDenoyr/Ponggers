#include "Game.hpp"

int Game::reset(Ball &p_ball, Paddle &p_p1, Paddle &p_p2){
    int pconv[6] = {1,3,5,10,100,-1};
    p_ball.mid(); p_p1.mid(); p_p2.mid();
    p_ball.setTexture(window.tex[BALL_W]);
    for(int jj = 0; jj < powers.size(); jj++){
        powers[jj].time = 0;
    }
    powerMovement(p_ball,p_p1,p_p2);
    powers.erase(powers.begin(),powers.end());
    hasLaunched = 0;
    if(score[0] == pconv[point_limit]){
        return 1;
    } else if(score[1] == pconv[point_limit]){
        return 2;
    }
    return 0; 
}

void Game::start(Ball &p_ball){
    long long int rn1 = SDL_GetTicks64()%5, rn2 = 2*(SDL_GetTicks64()%2) - 1;
    float choose[5] = {1.25f, 2.10f, 3.00f, 4.10f, 5.25f};
    float strt_spd[6] = {choose[rn1], 1.25f, 2.10f, 3.00f, 4.10f, 5.25f};
    int strt_dir[3] = {(int)rn2,1,-1};
    hasLaunched = 1;
    p_ball.setspeed((strt_dir[direction])*(strt_spd[speed_level]*1.25f),0.01f);
}

bool Game::moveBall(Ball &p_ball, Paddle& p_p1, Paddle& p_p2)
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
            audio.playSound(SOUND_Collision,0,1);
            p_ball.setTexture(window.tex[BALL_B]);
            p_ball.getPos().x = 46;
            p_ball.getxs() *= -1;
            if(std::abs(p_ball.getxs()) <= 10){
                p_ball.getxs() *= spi[speed_increaser];
            }
            if(std::abs(p_ball.getys()) <= 10){
                float curvefactor = std::abs(p_ball.getxs())*(p_ball.getPos().y - p_p1.getPos().y - p_p1.getPos().h/2 + 8.0f)/180.0f;
                p_ball.getys() += curvefactor;
            }
        }
    } else if(cdt_passed_p2){
        if(cdt_fronts_p2){
            audio.playSound(SOUND_Collision,0,1);
            p_ball.setTexture(window.tex[BALL_R]);
            p_ball.getPos().x = 898;
            p_ball.getxs() *= -1;
            if(std::abs(p_ball.getxs()) <= 10){
                p_ball.getxs() *= spi[speed_increaser];
            }
            if(std::abs(p_ball.getys()) <= 10){
                float curvefactor = std::abs(p_ball.getxs())*(p_ball.getPos().y - p_p2.getPos().y - p_p2.getPos().h/2 + 8.0f)/180.0f;
                p_ball.getys() += curvefactor;
            }
        }
    }
    if(p_ball.getPos().y < 0){
        audio.playSound(SOUND_Collision,0,1);
        p_ball.getPos().y = 0 + (0 - p_ball.getPos().y);
        p_ball.getys() *= -1;
    } else if(p_ball.getPos().y > 524){
        audio.playSound(SOUND_Collision,0,1);
        p_ball.getPos().y = 524 - (p_ball.getPos().y - 524);
        p_ball.getys() *= -1;
    }
    if(p_ball.getPos().x > 944){
        score[0]++;
        audio.playSound(SOUND_Point,0,1);
        return 1;

    } else if(p_ball.getPos().x < 0){
        score[1]++;
        audio.playSound(SOUND_Point,0,1);
        return 1;
    }
    return 0;
}

int Game::selectBasicPower(){
    long long int rng = SDL_GetTicks64()%4;
    std::vector<int> choose = {BPOW_ZAP,BPOW_INVERT,BPOW_GETBIG,BPOW_MAKESMALL};
    return choose[rng];
}

int Game::selectSpecialPower(){
    long long int rng = SDL_GetTicks64()%3;
    std::vector<int> choose = {SPOW_MIDWALL,SPOW_GRAVITY,SPOW_ANTIGRAVITY};
    return choose[rng];
}

void Game::addPower(bool p_powerType){
    int powerid, texid, time;
    if(p_powerType == 0){
        powerid = selectBasicPower();
    } else {
        powerid = selectSpecialPower();
    }
    switch (powerid) {
    case BPOW_ZAP:
        time = -1, texid = POWERBOX_ZAP;
        break;
    case SPOW_MIDWALL:
        time = 20*120, texid = POWERBOX_WALL;
        break;
    case SPOW_GRAVITY:
        time = 15*120, texid = POWERBOX_GRAV;
        break;
    case SPOW_ANTIGRAVITY:
        time = 15*120, texid = POWERBOX_ANTIGRAV;
        break;
    case BPOW_INVERT:
        time = -1, texid = POWERBOX_INVERT;
        break;
    case BPOW_GETBIG:
        time = 12*120, texid = POWERBOX_BIG;
        break;
    case BPOW_MAKESMALL:
        time = 12*120, texid = POWERBOX_SMALL;
        break;
    }
    int pos_spawn = window.getPos().w/2 - 130 + 110*(SDL_GetTicks64())%3;
    powers.push_back(Power(Vector2f(pos_spawn, 0, 40, 40),window.tex[texid],powerid,time));
}

void Game::powerMovement(Ball &p_ball, Paddle &p_p1, Paddle &p_p2){
    for(int ii = 0; ii < powers.size(); ii++){
        int c = powers[ii].powerId;
        if(powers[ii].active == 0){
            if(collisionwith(powers[ii],p_ball)){
                powers[ii].active = 1;
                audio.playSound(SOUND_Powerup,0,2);
                //Acoes iniciais de poderes continuos
                if(c == SPOW_GRAVITY || c == SPOW_ANTIGRAVITY){ //Gravidades
                    p_ball.getys() = 0;
                    p_ball.getxs() *= 0.8f;
                } else if(c == SPOW_MIDWALL){ //Parede
                    powers[ii].positions.push_back(new Entity(Vector2f(window.getPos().w/2 - 5, 100, 10, 165),window.tex[WALL]));
                    powers[ii].aux1 = -3;
                } else if(c == BPOW_GETBIG){ //Aumentar paddle
                    powers[ii].aux1 = p_ball.getxs();
                    if(powers[ii].aux1 > 0){
                        p_p1.setvar(50);
                        p_p1.getPos().h += 50;
                        p_p1.getPos().y -= 25;
                    } else {
                        p_p2.setvar(50);
                        p_p2.getPos().h += 50;
                        p_p2.getPos().y -= 25;
                    }
                    if(p_p1.getPos().y < 0) p_p1.getPos().y = 0;
                    if(p_p2.getPos().y < 0) p_p2.getPos().y = 0;
                    if(p_p1.getPos().y > window.getPos().h - p_p1.getPos().h) p_p1.getPos().y = window.getPos().h - p_p1.getPos().h;
                    if(p_p2.getPos().y > window.getPos().h - p_p2.getPos().h) p_p2.getPos().y = window.getPos().h - p_p2.getPos().h;
                } else if(c == BPOW_MAKESMALL){ //Diminuir paddle
                    powers[ii].aux1 = p_ball.getxs();
                    if(powers[ii].aux1 < 0){
                        p_p1.setvar(-30);
                        p_p1.getPos().h -= 30;
                        p_p1.getPos().y += 15;
                    } else {
                        p_p2.setvar(-30);
                        p_p2.getPos().h -= 30;
                        p_p2.getPos().y += 15;
                    }
                }
            } else {
                if(powers[ii].getPos().y >= window.getPos().h - powers[ii].getPos().h){
                    powers.erase(powers.begin()+ii);
                } else {
                    powers[ii].fall(6);
                }
            }
        } else {
            if(powers[ii].time > 0){ //Poderes continuos
                if(powers[ii].time == 140) audio.playSound(SOUND_Unpower,0,2); 
                if(c == SPOW_GRAVITY){ //Gravidade
                    p_ball.getys() += 0.12;
                    powers[ii].time--;
                } else if(c == SPOW_ANTIGRAVITY){ //Antigravidade
                    p_ball.getys() -= 0.12;
                    powers[ii].time--;
                } else if(c == SPOW_MIDWALL){ //Parede
                    Entity &entt = *powers[ii].positions[0];
                    if(collisionwith(p_ball, entt)){
                        p_ball.getxs() *= -1;
                        audio.playSound(SOUND_Collision,0,1);
                        if(p_ball.getxs() > 0){
                            powers[ii].positions[0]->setTexture(window.tex[WALL_RED]);
                            p_ball.getPos().x = window.getPos().w/2 + 6;
                        } else {
                            powers[ii].positions[0]->setTexture(window.tex[WALL_BLUE]);
                            p_ball.getPos().x = window.getPos().w/2 - 6 - p_ball.getPos().w;
                        }
                    }
                    if(powers[ii].positions[0]->getPos().y <= 80 || powers[ii].positions[0]->getPos().y >= window.getPos().h - 245){
                        powers[ii].aux1 *= -1;
                        powers[ii].positions[0]->getPos().y += powers[ii].aux1/4.0f;
                    } else {
                        powers[ii].positions[0]->getPos().y += powers[ii].aux1/4.0f;
                    }
                    powers[ii].time--;
                } else if(c == BPOW_GETBIG || c == BPOW_MAKESMALL){ //Modificar paddle
                    powers[ii].time--;
                }
            } else if(powers[ii].time == -1){ //Poderes instantaneos
                if(c == BPOW_ZAP){ //Zap
                    if(p_ball.getys()){
                        p_ball.getys() += 2.6*(p_ball.getys()/abs(p_ball.getys()));
                        p_ball.getxs() *= 0.8;
                    } else {
                        p_ball.getys() = 4;
                        p_ball.getxs() *= 0.8;
                    }
                } else if(c == BPOW_INVERT){ //Inverter
                    p_ball.getys() *= -1;
                }
                powers.erase(powers.begin()+ii);
            } else { //Encerrar poderes continuos
                if(c == SPOW_MIDWALL){ //Parede
                    for(Entity* k : powers[ii].positions){
                        delete k;
                    }
                } else if(c == SPOW_ANTIGRAVITY || c == SPOW_GRAVITY){ //Gravidades
                    p_ball.getys() = 0;
                    p_ball.getxs() *= 1.25f;
                } else if(c == BPOW_GETBIG){ //Aumentar paddle
                    if(powers[ii].aux1 > 0){
                        p_p1.setvar(0);
                        p_p1.getPos().h = 100;
                        p_p1.getPos().y += 20;
                    } else {
                        p_p2.setvar(0);
                        p_p2.getPos().h = 100;
                        p_p2.getPos().y += 20;
                    }
                } else if(c == BPOW_MAKESMALL){ //Diminuir paddle
                    if(powers[ii].aux1 < 0){
                        p_p1.setvar(0);
                        p_p1.getPos().h = 100;
                        p_p1.getPos().y -= 15;
                    } else {
                        p_p2.setvar(0);
                        p_p2.getPos().h = 100;
                        p_p2.getPos().y -= 15;
                    }
                    if(p_p1.getPos().y < 0) p_p1.getPos().y = 0;
                    if(p_p2.getPos().y < 0) p_p2.getPos().y = 0;
                    if(p_p1.getPos().y > window.getPos().h - p_p1.getPos().h) p_p1.getPos().y = window.getPos().h - p_p1.getPos().h;
                    if(p_p2.getPos().y > window.getPos().h - p_p2.getPos().h) p_p2.getPos().y = window.getPos().h - p_p2.getPos().h;
                }
                powers.erase(powers.begin()+ii);
            }
        }
    }
}