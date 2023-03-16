#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height) : window(NULL), renderer(NULL) { //Construtor da janela e renderizador
    window = SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_width,p_height,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!window){
        std::cout << "Falha ao criar janela. Erro:" << SDL_GetError() << std::endl;
    }
    pos.x = 0, pos.y = 0;
    pos.h = p_height, pos.w = p_width;
    textureStart();
}

void RenderWindow::textureStart(){
    // Preparar criação de texturas
    font = TTF_OpenFont("res/fonts/Peepo.ttf", 36);
    SDL_Color logo_color = {185, 215, 255, 0};
    SDL_Color white_color = {255, 255, 255, 0};

    // Criar superfícies para texturas por texto
    std::vector<SDL_Surface*> temp_s = 
    {
        TTF_RenderText_Solid(font,"P O N G G E R S",logo_color),
        TTF_RenderText_Solid(font,"Controles",white_color),
        TTF_RenderText_Solid(font,"Mover jogador 1",white_color),
        TTF_RenderText_Solid(font,"Mover jogador 2",white_color),
        TTF_RenderText_Solid(font,"Ativar movimento da bola",white_color),
        TTF_RenderText_Solid(font,"Voltar ao menu principal",white_color)
    };
    // Criar texturas por imagem e por texto
    tex.push_back(loadTexture("res/images/buttons/button_play.png"));
    tex.push_back(loadTexture("res/images/buttons/button_config.png"));
    tex.push_back(loadTexture("res/images/buttons/button_controls.png"));
    tex.push_back(loadTexture("res/images/controls/w_s.png"));
    tex.push_back(loadTexture("res/images/controls/up_down.png"));
    tex.push_back(loadTexture("res/images/controls/spacebar.png"));
    tex.push_back(loadTexture("res/images/controls/esc.png"));
    tex.push_back(loadTexture("res/images/buttons/button_return.png"));
    for(SDL_Surface* s : temp_s){
        tex.push_back(loadTexture(s));
    }
}

RenderWindow::~RenderWindow(){
    SDL_HideWindow(window);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

Vector2f& RenderWindow::getPos(){ // Retorna posição e tamanho da janela
    return pos;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){ //Carrega uma textura dos recursos
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer,p_filePath);
    if(!texture) std::cout << "Falha ao gerar textura. Erro:" << SDL_GetError() << std::endl;
    return texture;
}

SDL_Texture* RenderWindow::loadTexture(SDL_Surface* p_surface){ //Carrega uma textura dos recursos
    SDL_Texture* texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer,p_surface);
    if(!texture) std::cout << "Falha ao gerar textura. Erro:" << SDL_GetError() << std::endl;
    return texture;
}

void RenderWindow::clear(){ //Limpa o renderizador
    SDL_RenderClear(renderer);
}

void RenderWindow::display(){ //Desenha a tela renderizada atual
    SDL_RenderPresent(renderer);
}

void RenderWindow::render(Entity& p_entity){ //Renderiza objeto
    SDL_Rect dst;
    dst.x = p_entity.getPos().x;
    dst.y = p_entity.getPos().y;
    dst.w = p_entity.getPos().w;
    dst.h = p_entity.getPos().h;
    SDL_RenderCopy(renderer,p_entity.getTexture(),NULL,&dst);
}
