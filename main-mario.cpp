#include <cstdlib>
#include "Game.h"

int main(int argc, char** argv) {

    Game *p1 = Game::Instance();
    
    p1->Init();
    
    while (p1->window->isOpen()){
        
        p1->Input();
        
        p1->Update();
        
        p1->Render();
        
    }
    return 0;
}