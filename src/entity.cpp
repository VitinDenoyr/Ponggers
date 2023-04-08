#include "Entity.hpp"

Vector2f& Entity::getPos()
{
    return pos;
}

void Entity::setPos(Vector2f p_newpos){
    pos.x = p_newpos.x;
    pos.y = p_newpos.y;
    pos.w = p_newpos.w;
    pos.h = p_newpos.h;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

void Entity::setTexture(SDL_Texture* p_texture)
{
    texture = p_texture;
}

void Paddle::move(int p_dir){
    int v[5] = {2,3,4,6,8};
    if(getPos().y + p_dir*v[spd-1] < 0){
        getPos().y = 0;
    } else if(getPos().y + p_dir*v[spd-1] > 440 - paddle_variation){
        getPos().y = 440 - paddle_variation; 
    } else {
        getPos().y += p_dir*v[spd-1];
    }
}

void Paddle::mid(){
    getPos().y = 220;
}

void Paddle::setspeed(int p_speed){
    spd = p_speed;
}

void Paddle::setvar(int p_value){
    paddle_variation = p_value;
}

void Ball::mid()
{   
    ball_x_speed = 0; ball_y_speed = 0;
    getPos().x = 472;
    getPos().y = 262;
}

void Ball::setspeed(float p_xs, float p_ys){
    ball_x_speed = p_xs;
    ball_y_speed = p_ys;
}

float& Ball::getxs(){
    return ball_x_speed;
}

float& Ball::getys(){
    return ball_y_speed;
}

void Power::fall(int p_val){
    setPos({getPos().x,getPos().y + 0.1f*p_val,getPos().w,getPos().h});
}