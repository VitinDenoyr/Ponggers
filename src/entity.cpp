#include "Entity.hpp"

Vector2f& Entity::getPos(){
    return pos;
}

SDL_Texture* Entity::getTexture(){
    return texture;
}

void Paddle::middle(){
    getPos().y = 220; 
}

void Paddle::moveUp(){
    if(getPos().y-5 < 0){
        getPos().y = 0;
    } else {
        getPos().y -= 4;
    }
}

void Paddle::moveDown(){
    if(getPos().y+5 > (540-getPos().h)){
        getPos().y = 540-getPos().h;
    } else {
        getPos().y += 4;
    }
}

void Ball::ballIteration(float p_x, float p_y){
    getPos().x += p_x;
    getPos().y += p_y;
}

double Ball::xs(){
    return ball_xs;
}

double Ball::ys(){
    return ball_ys;
}

void Ball::setxs(double p_value){
    ball_xs = p_value;
}

void Ball::setys(double p_value){
    ball_ys = p_value;
}