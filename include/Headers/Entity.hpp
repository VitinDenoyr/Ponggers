#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Mathematics.hpp"

class Entity 
{
private:
    Vector2f pos;
    SDL_Texture* texture;
public:
    Entity(Vector2f p_pos, SDL_Texture* p_texture) : pos(p_pos), texture(p_texture){};
    Vector2f& getPos();
    SDL_Texture* getTexture();
};

class Ball : public Entity
{
private:
    double ball_xs, ball_ys;
public:
    Ball(Vector2f p_pos, SDL_Texture* p_texture) : Entity(p_pos, p_texture) , ball_xs(0) , ball_ys(0) {};
    Ball(Ball& p_ball, SDL_Texture* p_texture) : Entity(p_ball.getPos(),p_texture) {
        setxs(p_ball.xs());
        setys(p_ball.ys());
    };
    void ballIteration(float p_x, float p_y);
    double xs();
    double ys();
    void setxs(double p_value);
    void setys(double p_value);
};

class Paddle : public Entity
{
public:
    Paddle(Vector2f p_pos, SDL_Texture* p_texture) : Entity(p_pos, p_texture){};
    void moveUp();
    void moveDown();
    void middle();
};