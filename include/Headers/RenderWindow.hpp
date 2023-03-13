#pragma once
#include <iostream>
#include <SDL.H>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Entity.hpp"

class RenderWindow
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Vector2f size;
public:
    RenderWindow(const char* p_title, int p_width, int p_height);
    SDL_Texture* loadTexture(const char* p_filePath);
    Vector2f getSize();
    void memoryClear();
    void clear();
    void render(Entity& p_entity);
    void render(SDL_Surface* p_surface, SDL_Rect& p_rect);
    void display();
};