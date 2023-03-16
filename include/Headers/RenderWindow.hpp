#pragma once
#include <iostream>
#include <vector>
#include <SDL.H>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include "Fps.hpp"

class RenderWindow
{
private:
    TTF_Font* font;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Vector2f pos;
public:
    std::vector<SDL_Texture*> tex;
    RenderWindow(const char* p_title, int p_width, int p_height);
    ~RenderWindow();
    void textureStart();
    Vector2f& getPos();
    SDL_Texture* loadTexture(const char* p_filePath);
    SDL_Texture* loadTexture(SDL_Surface* p_surface);
    void clear();
    void display();
    void render(Entity& p_entity);
};

enum texture_id {
    PLAY, CONFIG, CONTROLS, BORDA_MOVE1, BORDA_MOVE2,
    BORDA_ATIVABOLA, BORDA_VOLTARAOMENU, VOLTAR , LOGO, TITULO_CONTROLES,
    TXT_MOVE1, TXT_MOVE2, TXT_ATIVABOLA, TXT_VOLTARAOMENU
};