#pragma once
#include <SDL.h>
#include <math.h>
#include <iostream>

class FPS
{
private:
    long double frameDuration;
    long double lastFrame, currentFrame;
    long double superior_frame_amount, superior_remainder;
public:
    long double updateAmount();
    void start();
    void update();
    void delay();
};