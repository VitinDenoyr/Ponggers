#pragma once
#include "WinScreen.hpp"
#include <map>
#define collisionwith(obj1,obj2) obj1.getPos().x + obj1.getPos().w >= obj2.getPos().x && obj1.getPos().y + obj1.getPos().h >= obj2.getPos().y && obj1.getPos().x <= obj2.getPos().x + obj2.getPos().w && obj1.getPos().y <= obj2.getPos().y + obj2.getPos().h

class Game
{
public:
    std::vector<Power> powers;
    int score[2]; Audio audio;
    RenderWindow window;
    //Poderes e variáveis
    bool basicPowers, specialPowers, use_ia;
    int speed_level, speed_increaser, player_speed;
    int direction, point_limit;
    bool adminMove;
    bool hasLaunched;
    //Construtor
    Game(Audio &p_audio, RenderWindow &p_window) : hasLaunched(0), basicPowers(0), specialPowers(0), adminMove(0), audio(p_audio), window(p_window), speed_level(2), speed_increaser(1), direction(0), use_ia(0), player_speed(3), point_limit(5) {}
    int reset(Ball &p_Ball, Paddle &p_p1, Paddle &p_p2);
    //Funcoes do jogo
    void start(Ball &p_ball);
    bool moveBall(Ball &p_ball, Paddle& p_p1, Paddle& p_p2);
    //Funcoes de poderes
    int selectBasicPower();
    int selectSpecialPower();
    void addPower(bool p_powerType);
    void powerMovement(Ball &p_ball, Paddle &p_p1, Paddle &p_p2);
};

enum bPower {
    BPOW_ZAP, BPOW_INVERT, BPOW_GETBIG, BPOW_MAKESMALL
};

enum sPower {
    SPOW_MIDWALL = 32, SPOW_GRAVITY, SPOW_ANTIGRAVITY
};