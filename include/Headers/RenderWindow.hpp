#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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
    void scoreUpdate(int p_score1, int p_score2, Entity &p_ent1, Entity &p_ent2);
    void alterTexture(const char* p_path, int p_texid);
    Vector2f& getPos();
    SDL_Texture* loadTexture(const char* p_filePath);
    SDL_Texture* loadTexture(SDL_Surface* p_surface);
    void clear();
    void display();
    void render(Entity &p_entity);
    void render(Entity &p_entity, Vector2f &p_portion);
};

enum texture_id {
    PLAY, CONFIG, CONTROLS, BORDA_MOVE1, BORDA_MOVE2,
    BORDA_ATIVABOLA, BORDA_VOLTARAOMENU, VOLTAR, 
    MARKBOX, MARKEDBOX, GRADE, BALL_R, BALL_B,
    BALL_W, PADDLE_1, PADDLE_2, ALT_RANDOM, ALT_1,
    ALT_2, ALT_3, ALT_4, ALT_5, ALT_0,
    ALT_R, ALT_L, ALT_I, ALT_III, ALT_V,
    ALT_X, ALT_C, ALT_INF, FIREWORK_1, FIREWORK_2, 
    P2_WIN, P2_LOSE, P1_WIN, P1_LOSE,

    LOGO, TITULO_CONTROLES, TXT_MOVE1, TXT_MOVE2, TXT_ATIVABOLA, 
    TXT_VOLTARAOMENU, TITULO_CONFIGURAR, PODERES_BASIC, PODERES_ESPECIAIS, SCORE1,
    SCORE2, SEPARATOR, VELOCIDADE_START, VELOCIDADE_ADD, BALL_DIRECTION,
    PLAY_AGAINST_AI, PLAYER_SPEED, POINT_LIMIT, VENCEDOR, JOG1, JOG2, ADMINLOGO
};

#define setarea(obj) mousex >= obj.getPos().x && mousey >= obj.getPos().y && mousex <= obj.getPos().x+obj.getPos().w && mousey <= obj.getPos().y+obj.getPos().h;