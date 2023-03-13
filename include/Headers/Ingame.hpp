#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Entity.hpp"
#include "RenderWindow.hpp"

class Game
{
private:
    RenderWindow window;
    int score[3];
    int SCREENWIDTH, SCREENHEIGHT;
    bool ball_active;
public:
    Game(int p_w, int p_h, RenderWindow& p_window)
    : SCREENWIDTH(p_w), SCREENHEIGHT(p_h), window(p_window) {};
    std::pair<int, int> getScores();
    void Reset(Ball &p_ball, Paddle &p_p1, Paddle &p_p2);
    void Launch(Ball& p_ball);
    void Point(int p_player, Ball& p_ball, Paddle& p_p1, Paddle& p_p2);
    void MoveBall(Ball& p_ball, Paddle& p_p1, Paddle& p_p2);
};