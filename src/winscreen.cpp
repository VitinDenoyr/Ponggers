#include "WinScreen.hpp"

bool winner(RenderWindow &window, Audio &audio, int p_player){
    // Recursos usados
    SDL_Cursor* cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor* cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    std::vector<Entity> entities_static = 
    {
        Entity(Vector2f(360,50,240,60),window.tex[VENCEDOR]),
        Entity(Vector2f((window.getPos().w-155)/2,462,155,60),window.tex[VOLTAR])
    };
    std::vector<Entity> entities_anim = 
    {
    };
    if(p_player == 1){
        entities_static.push_back(Entity(Vector2f(390,130,180,60),window.tex[JOG1]));
        entities_anim.push_back(Entity(Vector2f(660,30,200,200),window.tex[FIREWORK_2]));
        entities_anim.push_back(Entity(Vector2f(100,30,200,200),window.tex[FIREWORK_2]));
        entities_anim.push_back(Entity(Vector2f(200+50,240+95-(126)/2,126,126),window.tex[P1_WIN]));
        entities_anim.push_back(Entity(Vector2f(760-50-126,240+95-(126)/2,126,126),window.tex[P2_LOSE]));
    } else {
        entities_static.push_back(Entity(Vector2f(390,130,180,60),window.tex[JOG2]));
        entities_anim.push_back(Entity(Vector2f(660,30,200,200),window.tex[FIREWORK_1]));
        entities_anim.push_back(Entity(Vector2f(100,30,200,200),window.tex[FIREWORK_1]));
        entities_anim.push_back(Entity(Vector2f(200+50,240+95-(126)/2,126,126),window.tex[P1_LOSE]));
        entities_anim.push_back(Entity(Vector2f(760-50-126,240+95-(126)/2,126,126),window.tex[P2_WIN]));
    }
    std::vector<Vector2f> anim = 
    {
        Vector2f(0,0,200,200),
        Vector2f(0,0,200,200),
        Vector2f(0,0,126,126),
        Vector2f(0,0,126,126)
    };

    // Loop
    FPS fps; SDL_Event ev;
    bool winscstate = 1, quit = false;
    int framenumero = 0, framenumero2 = 0;
    fps.start();
    while(winscstate){
        fps.update();
        for(int i = 0; i < fps.updateAmount(); i++){
            // Atualizações
            int mousex, mousey;
            SDL_GetMouseState(&mousex,&mousey);

            bool condition_is_in_leave = setarea(entities_static[1]);

            if(condition_is_in_leave){
                SDL_SetCursor(cursor_hand);
            } else {
                SDL_SetCursor(cursor_arrow);
            }

            framenumero++;
            framenumero2++;
            while(SDL_PollEvent(&ev)){
                if(ev.type == SDL_QUIT){
                    return 0;
                } else if(ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT){
                    if(condition_is_in_leave){
                        winscstate = 0;
                    }
                }
            }
            const Uint8* keyboard = SDL_GetKeyboardState(NULL);
            if(keyboard[SDL_SCANCODE_ESCAPE])
            {
                winscstate = 0;
            }
            if(framenumero == 21)
            {
                framenumero = 0;
                anim[0].slide_r(9);
                anim[1].slide_r(9);
            }
            if(framenumero2 == 45)
            {
                framenumero2 = 0;
                anim[2].slide_r(2);
                anim[3].slide_r(2);
            }
        }
        fps.delay();

        // Renderizar e Desenhar
        window.clear();
        for(int j = 0; j < entities_anim.size(); j++){
            window.render(entities_anim[j],anim[j]);
        }
        for(int j = 0; j < entities_static.size(); j++){
            window.render(entities_static[j]);
        }
        window.display();
    }
    return 1;
}