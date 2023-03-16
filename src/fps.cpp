#include "Fps.hpp"

long double FPS::updateAmount(){
    return superior_frame_amount;
}

void FPS::start(){
    currentFrame = SDL_GetTicks64();
    frameDuration = 1000.0f / 120.0f;
}

void FPS::update(){
    lastFrame = currentFrame;
    currentFrame = SDL_GetTicks64();
    superior_frame_amount = std::ceil((currentFrame - lastFrame + 1) / frameDuration);
    superior_remainder = (superior_frame_amount * (frameDuration) - (currentFrame - lastFrame));
}

void FPS::delay(){
    float delayTime = std::max(0, (int)std::floor(superior_remainder - (SDL_GetTicks64() - currentFrame))); // Completar as operações anteriores - tempo ja gasto
    SDL_Delay(delayTime);
    currentFrame = SDL_GetTicks64();
}