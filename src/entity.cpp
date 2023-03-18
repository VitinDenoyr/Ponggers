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

void Paddle::move(float p_y){
    if(getPos().y + p_y < 0){
        getPos().y = 0;
    } else if(getPos().y + p_y > 440){
        getPos().y = 440; 
    } else {
        getPos().y += p_y;
    }
}

void Paddle::mid(){
    getPos().y = 220;
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
