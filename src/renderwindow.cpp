#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height) : window(NULL), renderer(NULL) { //Construtor de classe
    window = SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_width,p_height,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!window){
        std::cout << "Falha ao criar janela. Erro:" << SDL_GetError() << std::endl;
    }
    size.x = 0, size.y = 0;
    size.h = p_height, size.w = p_width;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){ //Carrega uma textura dos recursos
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer,p_filePath);
    if(!texture){
        std::cout << "Falha ao gerar textura. Erro:" << SDL_GetError() << std::endl;
    }
    return texture;
}

Vector2f RenderWindow::getSize(){
    return size;
}

void RenderWindow::clear(){ //Limpa o renderizador
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity){ //Renderiza objeto
    SDL_Rect dst;
    dst.x = p_entity.getPos().x;
    dst.y = p_entity.getPos().y;
    dst.w = p_entity.getPos().w;
    dst.h = p_entity.getPos().h;
    SDL_RenderCopy(renderer,p_entity.getTexture(),NULL,&dst);
}

void RenderWindow::render(SDL_Surface* p_surface, SDL_Rect& p_dst){ //Renderiza objeto
    SDL_Rect dst;
    dst.x = p_dst.x;
    dst.y = p_dst.y;
    dst.w = p_dst.w;
    dst.h = p_dst.h;
    SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer,p_surface);
    SDL_RenderCopy(renderer,score_texture,NULL,&dst);
}

void RenderWindow::display(){ //Desenha a tela renderizada atual
    SDL_RenderPresent(renderer);
}

void RenderWindow::memoryClear(){ //Limpa o que foi usado na tela da memória
    SDL_DestroyWindow(window);
}