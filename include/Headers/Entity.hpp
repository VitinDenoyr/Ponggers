#pragma once
#include <SDL.h>
#include "Math.hpp"

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
    float ball_x_speed, ball_y_speed;
public:
    Ball(Vector2f p_pos, SDL_Texture* p_texture) : Entity(p_pos, p_texture) , ball_x_speed(0) , ball_y_speed(0) {};
    void move(float p_x, float p_y);
};

class Paddle : public Entity
{
public:
    Paddle(Vector2f p_pos, SDL_Texture* p_texture) : Entity(p_pos, p_texture){};
    void move(float p_y);
    void mid();
};
