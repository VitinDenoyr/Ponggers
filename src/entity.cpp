#include "Entity.hpp"

Vector2f& Entity::getPos()
{
    return pos;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

void Ball::move(float p_x, float p_y)
{
    getPos().x += p_x;
    getPos().y += p_y;
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