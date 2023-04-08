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
    SDL_Color green_color = {15, 230, 145, 0};
    
    // Limpar tex
    for(SDL_Texture* s : tex){
        SDL_DestroyTexture(s);
    }
    tex.clear();

    // Criar texturas por imagem
    tex.push_back(loadTexture("res/images/controls/w_s.png"));
    tex.push_back(loadTexture("res/images/controls/up_down.png"));
    tex.push_back(loadTexture("res/images/controls/spacebar.png"));
    tex.push_back(loadTexture("res/images/controls/esc.png"));
    tex.push_back(loadTexture("res/images/buttons/click.png"));
    tex.push_back(loadTexture("res/images/buttons/clicked.png"));
    tex.push_back(loadTexture("res/images/grade.png"));
    tex.push_back(loadTexture("res/images/pong/ball_red.png"));
    tex.push_back(loadTexture("res/images/pong/ball_blue.png"));
    tex.push_back(loadTexture("res/images/pong/ball.png"));
    tex.push_back(loadTexture("res/images/pong/player_1.png"));
    tex.push_back(loadTexture("res/images/pong/player_2.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_rng.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_1.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_2.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_3.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_4.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_5.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_0.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_right.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_left.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_i.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_iii.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_v.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_x.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_c.png"));
    tex.push_back(loadTexture("res/images/buttons/altbox_inf.png"));
    tex.push_back(loadTexture("res/images/win/firework_yellow.png"));
    tex.push_back(loadTexture("res/images/win/firework_blue.png"));
    tex.push_back(loadTexture("res/images/win/red_cube_win.png"));
    tex.push_back(loadTexture("res/images/win/red_cube_lose.png"));
    tex.push_back(loadTexture("res/images/win/blue_cube_win.png"));
    tex.push_back(loadTexture("res/images/win/blue_cube_lose.png"));
    tex.push_back(loadTexture("res/images/pong/wall.png"));
    tex.push_back(loadTexture("res/images/pong/wall_R.png"));
    tex.push_back(loadTexture("res/images/pong/wall_B.png"));
    tex.push_back(loadTexture("res/images/powers/zap.png"));
    tex.push_back(loadTexture("res/images/powers/gravity.png"));
    tex.push_back(loadTexture("res/images/powers/antigravity.png"));
    tex.push_back(loadTexture("res/images/powers/wall.png"));
    tex.push_back(loadTexture("res/images/powers/invert.png"));
    tex.push_back(loadTexture("res/images/powers/biggify.png"));
    tex.push_back(loadTexture("res/images/powers/smallify.png"));
    // Criar texturas por texto/superfície
    std::vector<SDL_Surface*> temp_s = 
    {
        TTF_RenderText_Solid(font,"P O N G G E R S",logo_color),
        TTF_RenderText_Solid(font,"Controles",white_color),
        TTF_RenderText_Solid(font,"Mover jogador 1",white_color),
        TTF_RenderText_Solid(font,"Mover jogador 2",white_color),
        TTF_RenderText_Solid(font,"Ativar movimento da bola",white_color),
        TTF_RenderText_Solid(font,"Voltar ao menu principal",white_color),
        TTF_RenderText_Solid(font,"Configurar",white_color),
        TTF_RenderText_Solid(font,"Poderes basicos",white_color),
        TTF_RenderText_Solid(font,"Poderes especiais",white_color),
        TTF_RenderText_Solid(font,"0",white_color),
        TTF_RenderText_Solid(font,"0",white_color),
        TTF_RenderText_Solid(font,":",white_color),
        TTF_RenderText_Solid(font,"Velocidade inicial",white_color),
        TTF_RenderText_Solid(font,"Aumento de velocidade",white_color),
        TTF_RenderText_Solid(font,"Sentido inicial da bola",white_color),
        TTF_RenderText_Solid(font,"Jogar contra IA",white_color),
        TTF_RenderText_Solid(font,"Velocidade do jogador",white_color),
        TTF_RenderText_Solid(font,"Pontos para ganhar",white_color),
        TTF_RenderText_Solid(font,"Vencedor:",white_color),
        TTF_RenderText_Solid(font,"Jogador 1",{0,168,243,0}),
        TTF_RenderText_Solid(font,"Jogador 2",{236,28,36,0}),
        TTF_RenderText_Solid(font,"Portal do Admin",{177,25,212}),
        TTF_RenderText_Solid(font,"Voltar",white_color),
        TTF_RenderText_Solid(font,"Jogar",white_color),
        TTF_RenderText_Solid(font,"Controles",white_color),
        TTF_RenderText_Solid(font,"Configurar",white_color),
        TTF_RenderText_Solid(font,"Mover bola",white_color),
        TTF_RenderText_Solid(font,"Fundo secreto",white_color),
        TTF_RenderText_Solid(font,"Mover bola",green_color)
    };
    for(SDL_Surface* s : temp_s){
        tex.push_back(loadTexture(s));
    }
}

void RenderWindow::scoreUpdate(int p_score1, int p_score2, Entity &p_ent1, Entity &p_ent2){
    SDL_Color white_color = {255, 255, 255, 0};
    std::stringstream txt_s1; txt_s1 << p_score1;
    std::stringstream txt_s2; txt_s2 << p_score2;
    SDL_Surface* surface_s1 = TTF_RenderText_Solid(font, txt_s1.str().c_str(), white_color);
    SDL_Surface* surface_s2 = TTF_RenderText_Solid(font, txt_s2.str().c_str(), white_color);
    SDL_DestroyTexture(tex[SCORE1]); SDL_DestroyTexture(tex[SCORE2]);
    tex[SCORE1] = SDL_CreateTextureFromSurface(renderer,surface_s1);
    tex[SCORE2] = SDL_CreateTextureFromSurface(renderer,surface_s2);
    SDL_FreeSurface(surface_s1); SDL_FreeSurface(surface_s2);
    p_ent1 = Entity(Vector2f((getPos().w - 36 - 70 - 72*(txt_s1.str().length()-1))/2, 10, 36*(int)(txt_s1.str().length()) , 60),tex[SCORE1]);
    p_ent2 = Entity(Vector2f((getPos().w - 36 + 70)/2, 10, 36*(int)(txt_s2.str().length()) , 60),tex[SCORE2]);
}

void RenderWindow::alterTexture(const char* p_path, int p_texid){
    SDL_DestroyTexture(tex[p_texid]);
    tex[p_texid] = loadTexture(p_path);
}

RenderWindow::~RenderWindow(){
    SDL_HideWindow(window);
    for(SDL_Texture* s : tex){
        SDL_DestroyTexture(s);
    }
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

void RenderWindow::render(Entity& p_entity, Vector2f &p_portion){ //Renderiza objeto
    SDL_Rect dst;
    dst.x = p_entity.getPos().x;
    dst.y = p_entity.getPos().y;
    dst.w = p_entity.getPos().w;
    dst.h = p_entity.getPos().h;

    SDL_Rect src;
    src.x = p_portion.x;
    src.y = p_portion.y;
    src.w = p_portion.w;
    src.h = p_portion.h;

    SDL_RenderCopy(renderer,p_entity.getTexture(),&src,&dst);
}
