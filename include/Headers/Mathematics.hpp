#pragma once
#include <iostream>
#include <math.h>

struct Vector2f
{
    Vector2f()
    : x(0.0), y(0.0), h(0), w(0)
    {};

    Vector2f(float p_x, float p_y, int p_w, int p_h)
    : x(p_x), y(p_y), h(p_h), w(p_w)
    {};

    void print(){
        std::cout << x << "," << y << " de tamanho " << w << "x" << h << std::endl;
    };

    float x,y; int w,h;
};