#pragma once
#include "WinScreen.hpp"

class Game
{
private:
    bool hasLaunched; 
public:
    int score[2]; Audio audio;
    RenderWindow window;
    bool basicPowers, specialPowers, use_ia;
    int speed_level, speed_increaser, player_speed;
    int direction, point_limit;
    Game(Audio &p_audio, RenderWindow &p_window) : hasLaunched(0), basicPowers(0), specialPowers(0), audio(p_audio), window(p_window), speed_level(2), speed_increaser(1), direction(0), use_ia(0), player_speed(3), point_limit(5) {}
    int reset(Ball &p_Ball, Paddle &p_p1, Paddle &p_p2);
    bool gamestate();
    void start(Ball &p_ball);
    bool moveBall(Ball &p_ball, Paddle& p_p1, Paddle& p_p2);
};