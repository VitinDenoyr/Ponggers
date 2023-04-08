#pragma once
#include <SDL.h>
#include "Math.hpp"
#include "Mixer.hpp"
class Game;

class Entity 
{
private:
    Vector2f pos;
    SDL_Texture* texture;
public:
    Entity(Vector2f p_pos, SDL_Texture* p_texture) : pos(p_pos), texture(p_texture){};
    Vector2f& getPos();
    void setPos(Vector2f p_newpos);
    SDL_Texture* getTexture();
    void setTexture(SDL_Texture* p_texture);
    static Game* game;
};

class Paddle : public Entity
{
private:
    int spd, paddle_variation;
public:
    Paddle(Vector2f p_pos, SDL_Texture* p_texture) : Entity(p_pos, p_texture),paddle_variation(0) {};
    void move(int p_dir);
    void mid();
    void setspeed(int p_speed);
    void setvar(int p_value);
};

class Ball : public Entity
{
private:
    float ball_x_speed, ball_y_speed;
public:
    Ball(Vector2f p_pos, SDL_Texture* p_texture) : Entity(p_pos, p_texture) , ball_x_speed(0) , ball_y_speed(0) {};
    //int move(Paddle& p_p1, Paddle& p_p2);
    void mid();
    void setspeed(float p_xs, float p_ys);
    float& getxs();
    float& getys();
};

class Power : public Entity
{
public:
    Power(Vector2f p_pos, SDL_Texture* p_texture, int p_id, int p_time)
    : Entity(p_pos, p_texture), powerId(p_id), time(p_time), active(0) {};
    bool active;
    int powerId, time;
    int aux1, aux2;
    void fall(int p_val);
    std::vector<Entity*> positions;
};
