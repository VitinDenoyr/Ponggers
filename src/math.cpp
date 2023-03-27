#include "Math.hpp"

void Vector2f::slide_r(int p_qtimages){
    x += w;
    if(x >= w*p_qtimages){
        x = 0;
    }
}