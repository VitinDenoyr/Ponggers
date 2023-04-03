#pragma once
#include <iostream>

struct Vector2f
{
    float x,y; int w,h;
    Vector2f() : x(0.0), y(0.0), h(0), w(0) {};
    Vector2f(float p_x, float p_y) : x(p_x), y(p_y) {};
    Vector2f(float p_x, float p_y, int p_w, int p_h) : x(p_x), y(p_y), h(p_h), w(p_w) {};
    void slide_r(int p_qtimages);
};