#include <cstdlib>
#include "Game.h"

int main(int argc, char** argv) {

    Game *p1 = Game::Instance();
    
    p1->Init();        

    Time *clock = new Time(1.0f/game->iaSpeed);
    
    while (p1->window->isOpen()){
        
        if(clock->isExpired() == true){
            p1->Input();

            p1->Update();
        }
        
        p1->Render();
        
    }
    return 0;
}