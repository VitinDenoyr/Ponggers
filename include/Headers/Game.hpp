#pragma once
#include "RenderWindow.hpp"
#include "Mixer.hpp"

class Game
{
private:
    bool hasLaunched; 
public:
    int score[2]; Audio audio;
    bool basicPowers, specialPowers;
    int speed_level, speed_increaser;
    int direction;
    Game(Audio &p_audio) : hasLaunched(0), basicPowers(0), specialPowers(0), audio(p_audio), speed_level(2), speed_increaser(1), direction(0) {}
    void reset(Ball &p_Ball, Paddle &p_p1, Paddle &p_p2);
    bool gamestate();
    void start(Ball &p_ball);
    void moveBall(Ball &p_ball, Paddle& p_p1, Paddle& p_p2);
};